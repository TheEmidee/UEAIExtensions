#include "StateTree/Tasks/AIExtStateTreeTaskGetActorRotation.h"

#include "GameFramework/Actor.h"
#include "StateTreeExecutionContext.h"

FAIExtStateTreeTaskGetActorRotation::FAIExtStateTreeTaskGetActorRotation()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskGetActorRotation::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.Rotation = instance_data.Actor->GetActorRotation();

    return EStateTreeRunStatus::Running;
}