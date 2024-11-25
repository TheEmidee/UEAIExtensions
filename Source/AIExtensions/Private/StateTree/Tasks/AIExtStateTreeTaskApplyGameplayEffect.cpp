#include "StateTree/Tasks/AIExtStateTreeTaskApplyGameplayEffect.h"

#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <StateTreeExecutionContext.h>

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
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.EffectClass == nullptr )
    {
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
    }
    else
    {
        instance_data.Handle = instance_data.AbilitySystemComponent->ApplyGameplayEffectToSelf( gameplay_effect, instance_data.Level, effect_context_handle );
        instance_data.UsedASC = instance_data.AbilitySystemComponent;
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
    }
}