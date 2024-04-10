#include "Tasks/AIExtAITask_ActivateAbility.h"

#include <AIController.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <GameFramework/PlayerState.h>

UAIExtAITask_ActivateAbility::UAIExtAITask_ActivateAbility( const FObjectInitializer & object_initializer ) :
    Super( object_initializer ),
    bEndsWhenAbilityEnds( false ),
    bWasActivationSuccessful( false ),
    bDidAbilityEnd( false )
{
}

UAIExtAITask_ActivateAbility * UAIExtAITask_ActivateAbility::ActivateAbilityByClass( AAIController * controller, TSubclassOf< UGameplayAbility > ability_class, bool end_when_ability_ends, bool bLockAILogic )
{
    if ( auto * task = CreateTask( controller, end_when_ability_ends, bLockAILogic ) )
    {
        task->AbilityClass = ability_class;
        return task;
    }

    return nullptr;
}

UAIExtAITask_ActivateAbility * UAIExtAITask_ActivateAbility::ActivateAbilityByTag( AAIController * controller, FGameplayTag gameplay_tag, bool end_when_ability_ends, bool bLockAILogic )
{
    if ( auto * task = CreateTask( controller, end_when_ability_ends, bLockAILogic ) )
    {
        task->AbilityTag = gameplay_tag;
        return task;
    }

    return nullptr;
}

void UAIExtAITask_ActivateAbility::Setup( AAIController & ai_controller, UAbilitySystemComponent & asc, bool end_when_ability_ends, TSubclassOf< UGameplayAbility > ability_class )
{
    OwnerController = &ai_controller;
    ASC = &asc;
    bEndsWhenAbilityEnds = end_when_ability_ends;
    AbilityClass = ability_class;
}

void UAIExtAITask_ActivateAbility::Setup( AAIController & ai_controller, UAbilitySystemComponent & asc, bool end_when_ability_ends, FGameplayTag gameplay_tag )
{
    OwnerController = ai_controller;
    ASC = &asc;
    bEndsWhenAbilityEnds = end_when_ability_ends;
    AbilityTag = gameplay_tag;
}

void UAIExtAITask_ActivateAbility::ExternalCancel()
{
    ASC->CancelAbilityHandle( AbilitySpecHandle );
    EndTask();
}

UAIExtAITask_ActivateAbility * UAIExtAITask_ActivateAbility::CreateTask( AAIController * controller, bool end_when_ability_ends, bool bLockAILogic )
{
    auto * task = controller
                      ? UAITask::NewAITask< UAIExtAITask_ActivateAbility >( *controller, EAITaskPriority::High )
                      : nullptr;

    if ( task != nullptr )
    {
        if ( bLockAILogic )
        {
            task->RequestAILogicLocking();
        }

        task->bEndsWhenAbilityEnds = end_when_ability_ends;
        task->OwnerController = controller;

        auto * asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent( controller );

        if ( asc == nullptr )
        {
            asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent( controller->GetPawn() );
        }
        if ( asc == nullptr )
        {
            asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent( controller->GetPlayerState< APlayerState >() );
        }

        task->ASC = asc;
    }

    return task;
}

bool UAIExtAITask_ActivateAbility::TryActivateAbilityByHandle( UAbilitySystemComponent & asc, FGameplayAbilitySpecHandle ability_spec_handle )
{
    FGameplayTagContainer failure_tags;
    const FGameplayAbilitySpec * spec = asc.FindAbilitySpecFromHandle( ability_spec_handle );

    if ( spec == nullptr )
    {
        UE_VLOG( GetGameplayTasksComponent(), LogGameplayTasks, Warning, TEXT( "Invalid ability spec" ) );
        return false;
    }

    // don't activate abilities that are waiting to be removed
    if ( spec->PendingRemove || spec->RemoveAfterActivation )
    {
        return false;
    }

    const UGameplayAbility * ability = spec->Ability;

    if ( ability == nullptr )
    {
        UE_VLOG( GetGameplayTasksComponent(), LogGameplayTasks, Warning, TEXT( "Invalid ability " ) );
        return false;
    }

    const FGameplayAbilityActorInfo * actor_info = asc.AbilityActorInfo.Get();

    // make sure the ActorInfo and then Actor on that FGameplayAbilityActorInfo are valid, if not bail out.
    if ( actor_info == nullptr || !actor_info->OwnerActor.IsValid() || !actor_info->AvatarActor.IsValid() )
    {
        UE_VLOG( GetGameplayTasksComponent(), LogGameplayTasks, Warning, TEXT( "Invalid ActorInfo " ) );
        return false;
    }

    // This should only come from button presses/local instigation (AI, etc).
    if ( actor_info->AvatarActor->GetLocalRole() != ROLE_Authority )
    {
        UE_VLOG( GetGameplayTasksComponent(), LogGameplayTasks, Warning, TEXT( "Must have authority" ) );
        return false;
    }

    OnGameplayAbilityEndedDelegate.BindUObject( this, &ThisClass::OnGameplayAbilityEnded );

    if ( !asc.InternalTryActivateAbility( ability_spec_handle, FPredictionKey(), nullptr, &OnGameplayAbilityEndedDelegate ) )
    {
        return false;
    }

    return true;
}

void UAIExtAITask_ActivateAbility::OnGameplayAbilityEnded( UGameplayAbility * /*ability*/ )
{
    bDidAbilityEnd = true;

    if ( bEndsWhenAbilityEnds )
    {
        EndTask();
    }
}

void UAIExtAITask_ActivateAbility::Activate()
{
    Super::Activate();

    if ( ASC == nullptr )
    {
        EndTask();
        return;
    }

    if ( AbilityClass != nullptr )
    {
        const UGameplayAbility * const InAbilityCDO = AbilityClass.GetDefaultObject();

        for ( const FGameplayAbilitySpec & spec : ASC->GetActivatableAbilities() )
        {
            if ( spec.Ability == InAbilityCDO )
            {
                AbilitySpecHandle = spec.Handle;
                break;
            }
        }
    }
    else if ( AbilityTag.IsValid() )
    {
        // Copied from UAbilitySystemComponent::TryActivateAbilitiesByTag
        TArray< FGameplayAbilitySpec * > abilities_to_activate;
        ASC->GetActivatableGameplayAbilitySpecsByAllMatchingTags( FGameplayTagContainer( AbilityTag ), abilities_to_activate );

        if ( !abilities_to_activate.IsEmpty() )
        {
            AbilitySpecHandle = abilities_to_activate[ 0 ]->Handle;
        }
    }

    auto end_task = true;

    if ( AbilitySpecHandle.IsValid() )
    {
        const auto could_activate_ability = TryActivateAbilityByHandle( *ASC, AbilitySpecHandle );
        end_task = !could_activate_ability;

        if ( could_activate_ability && !bEndsWhenAbilityEnds )
        {
            end_task = true;
        }
    }

    if ( end_task )
    {
        EndTask();
    }
}

void UAIExtAITask_ActivateAbility::OnDestroy( bool bInOwnerFinished )
{
    OnGameplayAbilityEndedDelegate.Unbind();

    Super::OnDestroy( bInOwnerFinished );
}
