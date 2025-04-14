#include "StateTree/Tasks/AIExtStateTreeTaskEnableComponentCollision.h"

#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskEnableComponentCollision::FAIExtStateTreeTaskEnableComponentCollision()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskEnableComponentCollision::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Component != nullptr )
    {
        instance_data.Component->SetCollisionEnabled( instance_data.NewCollisionType );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}