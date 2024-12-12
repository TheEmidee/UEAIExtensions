#include "StateTree/Tasks/AIExtStateTreeTaskShowActor.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskShowActor::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Actor != nullptr )
    {
        instance_data.Actor->SetActorHiddenInGame( !instance_data.bIsVisible );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}