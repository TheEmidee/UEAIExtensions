#include "StateTree/Conditions/AIExtStateTreeConditionCanReachLocation.h"

#include <AITypes.h>
#include <StateTreeExecutionContext.h>

bool FAIExtStateTreeConditionCanReachLocation::TestCondition( FStateTreeExecutionContext & context ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    return FAISystem::IsValidLocation( instance_data.Location );
}