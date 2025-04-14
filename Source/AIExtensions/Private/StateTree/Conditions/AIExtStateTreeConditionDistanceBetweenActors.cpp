#include "StateTree/Conditions/AIExtStateTreeConditionDistanceBetweenActors.h"

#include "StateTree/AIExtStateTreeHelpers.h"

#include <StateTreeExecutionContext.h>

bool FAIExtStateTreeConditionDistanceBetweenActors::TestCondition( FStateTreeExecutionContext & context ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.FirstActor == nullptr || instance_data.SecondActor == nullptr )
    {
        return false;
    }

    const auto distance = FVector::Distance( instance_data.FirstActor->GetActorLocation(), instance_data.SecondActor->GetActorLocation() );

    const auto result = AIExtensions::CompareNumbers< double >( distance, instance_data.Distance, Operator );
    return result ^ bInvert;
}
