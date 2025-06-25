#include "StateTree/Conditions/AIExtStateTreeConditionDistanceXY.h"

#include "StateTree/AIExtStateTreeHelpers.h"

#include <StateTreeExecutionContext.h>

bool FAIExtStateTreeConditionDistanceXY::TestCondition( FStateTreeExecutionContext & context ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    const FVector::FReal Left = FVector::DistSquaredXY( instance_data.Source, instance_data.Target );
    const FVector::FReal Right = FMath::Square( instance_data.Distance );
    const bool result = AIExtensions::CompareNumbers< FVector::FReal >( Left, Right, Operator );

    return result ^ bInvert;
}