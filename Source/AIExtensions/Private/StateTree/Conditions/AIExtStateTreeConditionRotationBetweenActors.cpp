#include "StateTree/Conditions/AIExtStateTreeConditionRotationBetweenActors.h"

#include "StateTree/AIExtStateTreeHelpers.h"

#include <Kismet/KismetMathLibrary.h>
#include <StateTreeExecutionContext.h>

bool FAIExtStateTreeConditionRotationBetweenActors::TestCondition( FStateTreeExecutionContext & context ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.FirstActor == nullptr || instance_data.SecondActor == nullptr )
    {
        return false;
    }

    const auto delta_rotator = UKismetMathLibrary::NormalizedDeltaRotator( instance_data.FirstActor->GetActorRotation(), instance_data.SecondActor->GetActorRotation() );
    const auto angle = delta_rotator.GetComponentForAxis( static_cast< EAxis::Type >( static_cast< uint8 >( instance_data.Axis ) + 1 ) );

    const auto result = AIExtensions::CompareNumbers< double >( angle, instance_data.DeltaAngleThreshold, Operator );
    return result ^ bInvert;
}
