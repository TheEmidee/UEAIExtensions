#include "StateTree/Tasks/AIExtStateTreeTaskGetAIController.h"

#include "GameFramework/Pawn.h"
#include "StateTreeExecutionContext.h"

FAIExtStateTreeTaskGetAIController::FAIExtStateTreeTaskGetAIController()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskGetAIController::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Pawn == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.AIController = instance_data.Pawn->GetController< AAIController >();

    return EStateTreeRunStatus::Running;
}