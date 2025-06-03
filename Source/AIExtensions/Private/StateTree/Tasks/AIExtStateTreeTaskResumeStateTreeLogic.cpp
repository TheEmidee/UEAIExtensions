#include "StateTree/Tasks/AIExtStateTreeTaskResumeStateTreeLogic.h"

#include <Components/StateTreeComponent.h>
#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskResumeStateTreeLogic::FAIExtStateTreeTaskResumeStateTreeLogic()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskResumeStateTreeLogic::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.StateTreeComponent != nullptr )
    {
        instance_data.StateTreeComponent->ResumeLogic( instance_data.ResumeReason );
    }

    return EStateTreeRunStatus::Running;
}
