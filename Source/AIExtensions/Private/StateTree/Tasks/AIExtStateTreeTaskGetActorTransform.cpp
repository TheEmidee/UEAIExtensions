#include "StateTree/Tasks/AIExtStateTreeTaskGetActorTransform.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskGetActorTransform::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.Transform = instance_data.Actor->GetActorTransform();

    return EStateTreeRunStatus::Running;
}