#include "StateTree/Tasks/AIExtStateTreeTaskForceFinishState.h"

#include "StateTreeExecutionContext.h"
#include "VisualLogger/VisualLogger.h"

FAIExtStateTreeTaskForceFinish::FAIExtStateTreeTaskForceFinish()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskForceFinish::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskForceFinish." ) );

    return instance_data.bSucceeded
               ? EStateTreeRunStatus::Succeeded
               : EStateTreeRunStatus::Failed;
}