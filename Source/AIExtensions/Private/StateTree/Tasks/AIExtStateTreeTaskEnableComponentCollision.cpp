#include "StateTree/Tasks/AIExtStateTreeTaskEnableComponentCollision.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskEnableComponentCollision::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    const auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Component != nullptr )
    {
        instance_data.Component->SetCollisionEnabled( instance_data.NewCollisionType );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}