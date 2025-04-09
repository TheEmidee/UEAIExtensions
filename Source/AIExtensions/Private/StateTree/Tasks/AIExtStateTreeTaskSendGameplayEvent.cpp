#include "StateTree/Tasks/AIExtStateTreeTaskSendGameplayEvent.h"

#include "AbilitySystemComponent.h"

#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskSendGameplayEvent::FAIExtStateTreeTaskSendGameplayEvent()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskSendGameplayEvent::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    auto asc = instance_data.TargetASC;

    if ( asc == nullptr )
    {
        asc = instance_data.Target ? instance_data.Target->FindComponentByClass< UAbilitySystemComponent >() : nullptr;
    }

    if ( asc == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskSendGameplayEvent failed because there's no ability system component to send the gameplay event to." ) );
        return EStateTreeRunStatus::Failed;
    }

    FScopedPredictionWindow new_scoped_window( asc, true );
    FGameplayEventData payload;
    payload.EventTag = instance_data.EventTag;
    payload.EventMagnitude = instance_data.PayloadEventMagnitude;
    payload.Instigator = instance_data.PayloadInstigator;
    payload.InstigatorTags = instance_data.PayloadInstigatorTags;
    payload.Target = instance_data.PayloadTarget;
    payload.TargetTags = instance_data.PayloadTargetTags;
    payload.OptionalObject = instance_data.PayloadOptionalObject;
    payload.OptionalObject2 = instance_data.PayloadOptionalObject2;

    asc->HandleGameplayEvent( instance_data.EventTag, &payload );

    return EStateTreeRunStatus::Running;
}