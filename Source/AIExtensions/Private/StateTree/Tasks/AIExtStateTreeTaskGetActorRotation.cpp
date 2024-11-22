#include "StateTree/Tasks/AIExtStateTreeTaskGetActorRotation.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskGetActorRotation::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.Rotation = instance_data.Actor->GetActorRotation();

    return EStateTreeRunStatus::Running;
}