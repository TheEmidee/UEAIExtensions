#include "StateTree/Tasks/AIExtStateTreeTaskPauseStateTreeLogic.h"

#include <Components/StateTreeComponent.h>
#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskPauseStateTreeLogic::FAIExtStateTreeTaskPauseStateTreeLogic()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskPauseStateTreeLogic::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.StateTreeComponent != nullptr )
    {
        instance_data.StateTreeComponent->PauseLogic( instance_data.StopReason );
    }

    return EStateTreeRunStatus::Running;
}