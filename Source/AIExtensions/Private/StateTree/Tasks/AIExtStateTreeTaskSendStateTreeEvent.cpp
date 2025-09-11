#include "StateTree/Tasks/AIExtStateTreeTaskSendStateTreeEvent.h"

#include "Components/StateTreeComponent.h"
#include "StateTreeExecutionContext.h"

FAIExtStateTreeTaskSendStateTreeEvent::FAIExtStateTreeTaskSendStateTreeEvent()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskSendStateTreeEvent::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.StateTreeComponent != nullptr )
    {
        instance_data.StateTreeComponent->SendStateTreeEvent( instance_data.EventTag, instance_data.Payload, instance_data.Origin );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}