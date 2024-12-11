#include "StateTree/Tasks/AIExtStateTreeTaskSendStateTreeEvent.h"

#include <Components/StateTreeComponent.h>
#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskSendStateTreeEvent::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.StateTreeComponent != nullptr )
    {
        instance_data.StateTreeComponent->SendStateTreeEvent( instance_data.EventTag );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}