#include "StateTree/Conditions/AIExtStateTreeConditionDistanceBetweenActors.h"

#include <StateTreeExecutionContext.h>

namespace UE::StateTree::Conditions
{
    template < typename T >
    bool CompareNumbers( const T left, const T right, const EGenericAICheck operation )
    {
        switch ( operation )
        {
            case EGenericAICheck::Equal:
                return left == right;
            case EGenericAICheck::NotEqual:
                return left != right;
            case EGenericAICheck::Less:
                return left < right;
            case EGenericAICheck::LessOrEqual:
                return left <= right;
            case EGenericAICheck::Greater:
                return left > right;
            case EGenericAICheck::GreaterOrEqual:
                return left >= right;
            default:
                ensureMsgf( false, TEXT( "Unhandled operator %d" ), operation );
                return false;
        }
    }
} // UE::StateTree::Conditions

bool FAIExtStateTreeConditionDistanceBetweenActors::TestCondition( FStateTreeExecutionContext & context ) const
{
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.FirstActor == nullptr || instance_data.SecondActor == nullptr )
    {
        return false;
    }

    const auto distance = FVector::Distance( instance_data.FirstActor->GetActorLocation(), instance_data.SecondActor->GetActorLocation() );

    const auto result = UE::StateTree::Conditions::CompareNumbers< double >( distance, instance_data.Distance, Operator );
    return result ^ bInvert;
}
