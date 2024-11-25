#include "StateTree/Tasks/AIExtStateTreeTaskForceFinishState.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskForceFinish::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    return instance_data.bSucceeded
               ? EStateTreeRunStatus::Succeeded
               : EStateTreeRunStatus::Failed;
}