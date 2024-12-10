#include "StateTree/Tasks/AIExtStateTreeTaskEnableActorCollision.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskEnableActorCollision::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Actor != nullptr )
    {
        instance_data.Actor->SetActorEnableCollision( instance_data.bCollisionEnabled );

        return EStateTreeRunStatus::Succeeded;
    }

    return EStateTreeRunStatus::Failed;
}