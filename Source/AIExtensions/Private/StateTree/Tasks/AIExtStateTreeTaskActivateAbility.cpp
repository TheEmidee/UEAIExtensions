#include "StateTree/Tasks/AIExtStateTreeTaskActivateAbility.h"

#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <StateTreeExecutionContext.h>

void UAIExtStateTreeTaskActivateAbilityInstanceData::OnAbilityEnded( const FAbilityEndedData & ability_ended_data )
{
    if ( !bEndTaskWhenAbilityEnds )
    {
        return;
    }

    if ( !AbilitySpecHandle.IsValid() ||
         ability_ended_data.bWasCancelled )
    {
        RunStatus = EStateTreeRunStatus::Failed;
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
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.AbilityClass == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    for ( const auto & ability_spec : instance_data.AbilitySystemComponent->GetActivatableAbilities() )
    {
        if ( ability_spec.Ability->GetClass() == instance_data.AbilityClass )
        {
            instance_data.AbilitySpecHandle = ability_spec.Handle;
            break;
        }
    }

    if ( !instance_data.AbilitySpecHandle.IsValid() )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.AbilitySystemComponent->OnAbilityEnded.AddUObject( &instance_data, &UAIExtStateTreeTaskActivateAbilityInstanceData::OnAbilityEnded );

    const auto could_activate_ability = instance_data.AbilitySystemComponent->TryActivateAbility( instance_data.AbilitySpecHandle );

    if ( !could_activate_ability && instance_data.bEndTaskWhenAbilityEnds )
    {
        return EStateTreeRunStatus::Failed;
    }

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAIExtStateTreeTaskActivateAbility::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
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
    }
}