#include "StateTree/Tasks/AIExtStateTreeTaskShowActor.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskShowActor::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Actor != nullptr )
    {
        instance_data.Actor->SetActorHiddenInGame( !instance_data.bIsVisible );

        return EStateTreeRunStatus::Succeeded;
    }

    return EStateTreeRunStatus::Failed;
}