#include "Tasks/AIExtAITask_TriggerGameplayBehavior.h"

#include "GameplayBehaviors/AIExtGameplayBehaviorDataAsset.h"

#include <AIController.h>
#include <GameplayBehaviorConfig.h>
#include <GameplayBehaviorSubsystem.h>

UAIExtAITask_TriggerGameplayBehavior::UAIExtAITask_TriggerGameplayBehavior( const FObjectInitializer & object_initializer ) :
    Super( object_initializer )
{
    bBehaviorFinished = false;
}

UAIExtAITask_TriggerGameplayBehavior * UAIExtAITask_TriggerGameplayBehavior::TriggerGameplayBehavior( AAIController * controller, UGameplayBehaviorConfig * gameplay_behavior_config, bool lock_ai_logic /* = true */, AActor * gameplay_behavior_owner /*= nullptr*/ )
{
    if ( controller == nullptr )
    {
        return nullptr;
    }

    if ( gameplay_behavior_config == nullptr )
    {
        return nullptr;
    }

    const auto * behavior = gameplay_behavior_config->GetBehavior( *controller->GetWorld() );

    if ( behavior == nullptr )
    {
        return nullptr;
    }

    auto * task = UAITask::NewAITask< UAIExtAITask_TriggerGameplayBehavior >( *controller, EAITaskPriority::High );
    if ( task == nullptr )
    {
        return nullptr;
    }

    task->GameplayBehaviorConfig = gameplay_behavior_config;
    task->GameplayBehaviorOwner = gameplay_behavior_owner;

    if ( lock_ai_logic )
    {
        task->RequestAILogicLocking();
    }

    return task;
}

UAIExtAITask_TriggerGameplayBehavior * UAIExtAITask_TriggerGameplayBehavior::TriggerGameplayBehaviorWithDataAsset( AAIController * controller, UAIExtGameplayBehaviorDataAsset * gameplay_behavior_data_asset, bool lock_ai_logic, AActor * gameplay_behavior_owner )
{
    if ( gameplay_behavior_data_asset == nullptr )
    {
        return nullptr;
    }

    if ( gameplay_behavior_data_asset->GameplayBehaviorConfig == nullptr )
    {
        return nullptr;
    }

    return TriggerGameplayBehavior( controller, gameplay_behavior_data_asset->GameplayBehaviorConfig.Get(), lock_ai_logic, gameplay_behavior_owner );
}

void UAIExtAITask_TriggerGameplayBehavior::OnDestroy( bool bInOwnerFinished )
{
    Abort();

    if ( TaskState != EGameplayTaskState::Finished )
    {
        if ( GameplayBehavior != nullptr )
        {
            OnSucceeded.Broadcast();
        }
        else
        {
            OnFailed.Broadcast();
        }

        Super::OnDestroy( bInOwnerFinished );
    }
}

void UAIExtAITask_TriggerGameplayBehavior::Activate()
{
    Super::Activate();

    bBehaviorFinished = false;
    ON_SCOPE_EXIT
    {
        if ( bBehaviorFinished )
        {
            EndTask();
        }
    };

    GameplayBehavior = GameplayBehaviorConfig->GetBehavior( *OwnerController->GetWorld() );

    bBehaviorFinished = !UGameplayBehaviorSubsystem::TriggerBehavior( *GameplayBehavior, *OwnerController->GetPawn(), GameplayBehaviorConfig, GameplayBehaviorOwner );
    // Behavior can be successfully triggered AND ended synchronously. We are only interested to register callback when still running
    if ( !bBehaviorFinished )
    {
        OnBehaviorFinishedNotifyHandle = GameplayBehavior->GetOnBehaviorFinishedDelegate().AddUObject( this, &ThisClass::OnGameplayBehaviorFinished );
    }
    else
    {
        bBehaviorFinished = true;
    }
}

void UAIExtAITask_TriggerGameplayBehavior::Abort()
{
    check( OwnerController );
    check( OwnerController->GetPawn() );

    if ( !bBehaviorFinished )
    {
        if ( GameplayBehavior != nullptr )
        {
            GameplayBehavior->GetOnBehaviorFinishedDelegate().Remove( OnBehaviorFinishedNotifyHandle );
            GameplayBehavior->AbortBehavior( *OwnerController->GetPawn() );
        }
    }
}

void UAIExtAITask_TriggerGameplayBehavior::OnGameplayBehaviorFinished( UGameplayBehavior & behavior, AActor & avatar, const bool interrupted )
{
    ensure( OwnerController != nullptr );

    // make sure we handle the right pawn - we can get this notify for a different
    // Avatar if the behavior sending it out is not instanced (CDO is being used to perform actions)
    if ( OwnerController && OwnerController->GetPawn() == &avatar )
    {
        behavior.GetOnBehaviorFinishedDelegate().Remove( OnBehaviorFinishedNotifyHandle );
        bBehaviorFinished = true;
        EndTask();
    }
}
