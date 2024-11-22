#include "StateTree/Tasks/AIExtStateTreeTaskGetAIController.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskGetAIController::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Pawn == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.AIController = instance_data.Pawn->GetController< AAIController >();

    return EStateTreeRunStatus::Running;
}