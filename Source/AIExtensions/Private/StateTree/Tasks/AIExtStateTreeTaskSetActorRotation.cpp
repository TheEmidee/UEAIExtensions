#include "StateTree/Tasks/AIExtStateTreeTaskSetActorRotation.h"

#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskSetActorRotation::FAIExtStateTreeTaskSetActorRotation()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskSetActorRotation::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Actor != nullptr )
    {
        instance_data.Actor->SetActorRotation( instance_data.Rotation );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}