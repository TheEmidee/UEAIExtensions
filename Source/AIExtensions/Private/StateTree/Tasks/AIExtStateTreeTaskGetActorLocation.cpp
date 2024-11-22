#include "StateTree/Tasks/AIExtStateTreeTaskGetActorLocation.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskGetActorLocation::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.Location = instance_data.Actor->GetActorLocation();

    return EStateTreeRunStatus::Running;
}