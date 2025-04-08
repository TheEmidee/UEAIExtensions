#include "StateTree/Tasks/AIExtStateTreeTaskGetActorTransform.h"

#include <GameFramework/Actor.h>
#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskGetActorTransform::FAIExtStateTreeTaskGetActorTransform()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskGetActorTransform::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.Transform = instance_data.Actor->GetActorTransform();

    return EStateTreeRunStatus::Running;
}