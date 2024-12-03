#include "StateTree/Tasks/AIExtStateTreeTaskGetDistanceBetweenActors.h"

#include <GameFramework/Actor.h>

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskGetDistanceBetweenActors::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor1 != nullptr && instance_data.OtherComponent != nullptr )
    {
        instance_data.Distance = FVector::Distance( instance_data.Actor1->GetActorLocation(), instance_data.OtherComponent->GetComponentLocation() );
    }
    else if ( instance_data.Actor1 != nullptr && instance_data.Actor2 != nullptr )
    {
        instance_data.Distance = FVector::Distance( instance_data.Actor1->GetActorLocation(), instance_data.Actor2->GetActorLocation() );
    }

    return EStateTreeRunStatus::Running;
}