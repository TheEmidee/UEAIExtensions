#include "BehaviorTree/AIExtBTTask_WaitBlackboardTimeWithDeviation.h"

#include <BehaviorTree/Blackboard/BlackboardKeyType_Float.h>
#include <BehaviorTree/BlackboardComponent.h>

void UAIExtBTTask_WaitBlackboardTimeWithDeviation::InitializeFromAsset( UBehaviorTree & asset )
{
    Super::InitializeFromAsset( asset );

    const auto * blackboard = GetBlackboardAsset();
    if ( ensure( blackboard != nullptr ) )
    {
        TimeBlackboardKey.ResolveSelectedKey( *blackboard );
        DeviationBlackboardKey.ResolveSelectedKey( *blackboard );
    }
}

FString UAIExtBTTask_WaitBlackboardTimeWithDeviation::GetStaticDescription() const
{
    return FString::Printf( TEXT( "%s: %s %s" ), *UBTTaskNode::GetStaticDescription(), *TimeBlackboardKey.SelectedKeyName.ToString(), *DeviationBlackboardKey.SelectedKeyName.ToString() );
}

EBTNodeResult::Type UAIExtBTTask_WaitBlackboardTimeWithDeviation::ExecuteTask( UBehaviorTreeComponent & owner_comp, uint8 * node_memory )
{
    const auto * blackboard_component = owner_comp.GetBlackboardComponent();

    if ( blackboard_component != nullptr &&
         TimeBlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass() &&
         DeviationBlackboardKey.SelectedKeyType == UBlackboardKeyType_Float::StaticClass() )
    {
        const auto time = blackboard_component->GetValue< UBlackboardKeyType_Float >( TimeBlackboardKey.GetSelectedKeyID() );
        const auto deviation = blackboard_component->GetValue< UBlackboardKeyType_Float >( DeviationBlackboardKey.GetSelectedKeyID() );

        WaitTime = FMath::FRandRange( FMath::Max( 0.0f, time - deviation ), time + deviation );
    }

    return Super::ExecuteTask( owner_comp, node_memory );
}
