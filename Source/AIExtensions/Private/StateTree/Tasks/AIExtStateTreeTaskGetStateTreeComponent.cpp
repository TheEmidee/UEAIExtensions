#include "StateTree/Tasks/AIExtStateTreeTaskGetStateTreeComponent.h"

#include <Components/StateTreeComponent.h>
#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskGetStateTreeComponent::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    instance_data.StateTreeComponent = instance_data.Actor->FindComponentByClass< UStateTreeComponent >();

    return EStateTreeRunStatus::Running;
}