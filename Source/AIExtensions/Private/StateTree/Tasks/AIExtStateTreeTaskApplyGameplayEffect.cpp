#include "StateTree/Tasks/AIExtStateTreeTaskApplyGameplayEffect.h"

#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <StateTreeExecutionContext.h>
#include <VisualLogger/VisualLogger.h>

EStateTreeRunStatus FAIExtStateTreeTaskApplyGameplayEffect::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

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
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskApplyGameplayEffect can't apply gameplay effect because no ability system was bound." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.EffectClass == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskApplyGameplayEffect can't apply gameplay effect because no gameplay effect is bound." ) );
        return EStateTreeRunStatus::Failed;
    }

    UAbilitySystemComponent * target_asc = instance_data.TargetAbilitySystemComponent;

    if ( target_asc == nullptr )
    {
        target_asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent( instance_data.TargetActor );
    }

    auto effect_context_handle = instance_data.AbilitySystemComponent->MakeEffectContext();
    auto * gameplay_effect = instance_data.EffectClass->GetDefaultObject< UGameplayEffect >();

    if ( target_asc != nullptr )
    {
        instance_data.Handle = instance_data.AbilitySystemComponent->ApplyGameplayEffectToTarget( gameplay_effect, target_asc, instance_data.Level, effect_context_handle );
        instance_data.UsedASC = target_asc;

        UE_VLOG( context.GetOwner(), LogStateTree, Log, FString::Printf( TEXT( "FAIExtStateTreeTaskApplyGameplayEffect applied gameplay effect %s on target." ), *GetNameSafe( instance_data.EffectClass ) ) );
    }
    else
    {
        instance_data.Handle = instance_data.AbilitySystemComponent->ApplyGameplayEffectToSelf( gameplay_effect, instance_data.Level, effect_context_handle );
        instance_data.UsedASC = instance_data.AbilitySystemComponent;

        UE_VLOG( context.GetOwner(), LogStateTree, Log, FString::Printf( TEXT( "FAIExtStateTreeTaskApplyGameplayEffect applied gameplay effect %s on self." ), *GetNameSafe( instance_data.EffectClass ) ) );
    }

    return EStateTreeRunStatus::Running;
}

void FAIExtStateTreeTaskApplyGameplayEffect::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.bRemoveEffectWhenTaskExits )
    {
        instance_data.UsedASC->RemoveActiveGameplayEffect( instance_data.Handle );
        UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskApplyGameplayEffect removed gameplay effect." ) );
    }
}