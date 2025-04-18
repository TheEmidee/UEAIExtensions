#include "StateTree/Tasks/AIExtStateTreeTaskActivateAbility.h"

#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <StateTreeExecutionContext.h>
#include <VisualLogger/VisualLogger.h>

void UAIExtStateTreeTaskActivateAbilityInstanceData::OnAbilityEnded( const FAbilityEndedData & ability_ended_data )
{
    if ( ability_ended_data.AbilitySpecHandle != AbilitySpecHandle )
    {
        return;
    }

    if ( !bEndTaskWhenAbilityEnds )
    {
        return;
    }

    if ( !AbilitySpecHandle.IsValid() ||
         ability_ended_data.bWasCancelled )
    {
        RunStatus = EStateTreeRunStatus::Failed;

        return;
    }

    RunStatus = EStateTreeRunStatus::Succeeded;
}

EStateTreeRunStatus FAIExtStateTreeTaskActivateAbility::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData< UInstanceDataType >( *this );

    if ( instance_data.AbilitySystemComponent == nullptr )
    {
        if ( instance_data.Actor == nullptr )
        {
            return EStateTreeRunStatus::Failed;
        }

        instance_data.AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent( instance_data.Actor );
    }

    if ( instance_data.AbilitySystemComponent == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskActivateAbility can't activate gameplay ability because no ability system was bound." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.AbilityClass == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskActivateAbility can't activate gameplay ability because no gameplay ability was bound." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.bGiveAbility )
    {
        instance_data.AbilitySpecHandle = instance_data.AbilitySystemComponent->K2_GiveAbility( instance_data.AbilityClass );
    }
    else
    {
        for ( const auto & ability_spec : instance_data.AbilitySystemComponent->GetActivatableAbilities() )
        {
            if ( ability_spec.Ability->GetClass() == instance_data.AbilityClass )
            {
                instance_data.AbilitySpecHandle = ability_spec.Handle;
                break;
            }
        }
    }

    if ( !instance_data.AbilitySpecHandle.IsValid() )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskActivateAbility can't activate gameplay ability because the ability was not granted to the actor." ) );
        return EStateTreeRunStatus::Failed;
    }

    instance_data.AbilitySystemComponent->OnAbilityEnded.AddUObject( &instance_data, &UAIExtStateTreeTaskActivateAbilityInstanceData::OnAbilityEnded );

    bool could_activate_ability = false;

    if ( instance_data.bSendGameplayEvent )
    {
        FGameplayEventData payload;
        payload.EventTag = instance_data.EventTag;
        payload.Instigator = instance_data.PayloadInstigator;
        payload.Target = instance_data.PayloadTarget;

        could_activate_ability = instance_data.AbilitySystemComponent->TriggerAbilityFromGameplayEvent(
            instance_data.AbilitySpecHandle,
            nullptr,
            FGameplayTag::EmptyTag,
            &payload,
            *instance_data.AbilitySystemComponent );
    }
    else
    {
        instance_data.AbilitySystemComponent->TryActivateAbility( instance_data.AbilitySpecHandle );
    }
    

    if ( !could_activate_ability && instance_data.bEndTaskWhenAbilityEnds )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskActivateAbility failed to activate the ability." ) );
        return EStateTreeRunStatus::Failed;
    }

    UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskActivateAbility successfully activated the ability." ) );
    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAIExtStateTreeTaskActivateAbility::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData< UInstanceDataType >( *this );

    return instance_data.RunStatus;
}

void FAIExtStateTreeTaskActivateAbility::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData< UInstanceDataType >( *this );

    if ( instance_data.AbilitySystemComponent == nullptr )
    {
        return;
    }

    instance_data.AbilitySystemComponent->OnAbilityEnded.RemoveAll( &instance_data );

    if ( instance_data.bEndTaskWhenAbilityEnds &&
         instance_data.AbilitySpecHandle.IsValid() )
    {
        instance_data.AbilitySystemComponent->CancelAbilityHandle( instance_data.AbilitySpecHandle );

        UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskActivateAbility cancelled gameplay ability." ) );
    }

    if ( instance_data.bRemoveAbility )
    {
        instance_data.AbilitySystemComponent->SetRemoveAbilityOnEnd( instance_data.AbilitySpecHandle );
    }
}