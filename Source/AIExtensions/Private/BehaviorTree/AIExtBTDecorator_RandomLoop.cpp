#include "BehaviorTree/AIExtBTDecorator_RandomLoop.h"

#include <BehaviorTree/BTCompositeNode.h>
#include <BehaviorTree/Composites/BTComposite_SimpleParallel.h>
#include <Engine/World.h>

UAIExtBTDecorator_RandomLoop::UAIExtBTDecorator_RandomLoop()
{
    NodeName = "RandomLoop";
    MinNumLoops = 1;
    MaxNumLoops = 3;
    NumLoops = 0;
    bNotifyActivation = true;

    bAllowAbortNone = false;
    bAllowAbortLowerPri = false;
    bAllowAbortChildNodes = false;
}

uint16 UAIExtBTDecorator_RandomLoop::GetInstanceMemorySize() const
{
    return sizeof( FAIExtBTRandomLoopDecoratorMemory );
}

void UAIExtBTDecorator_RandomLoop::DescribeRuntimeValues( const UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray< FString > & Values ) const
{
    Super::DescribeRuntimeValues( OwnerComp, NodeMemory, Verbosity, Values );

    const auto * decorator_memory = reinterpret_cast< FAIExtBTRandomLoopDecoratorMemory * >( NodeMemory );
    Values.Add( FString::Printf( TEXT( "loops remaining: %d" ), decorator_memory->RemainingExecutions ) );
}

FString UAIExtBTDecorator_RandomLoop::GetStaticDescription() const
{
    return FString::Printf( TEXT( "%s: [%i/%i] loops" ), *Super::GetStaticDescription(), MinNumLoops, MaxNumLoops );
}

#if WITH_EDITOR
FName UAIExtBTDecorator_RandomLoop::GetNodeIconName() const
{
    return FName( "BTEditor.Graph.BTNode.Decorator.Loop.Icon" );
}
#endif // WITH_EDITOR

void UAIExtBTDecorator_RandomLoop::OnNodeActivation( FBehaviorTreeSearchData & SearchData )
{
    auto * decorator_memory = GetNodeMemory< FAIExtBTRandomLoopDecoratorMemory >( SearchData );
    const auto * parent_memory = GetParentNode()->GetNodeMemory< FBTCompositeMemory >( SearchData );
    const auto is_special_node = GetParentNode()->IsA( UBTComposite_SimpleParallel::StaticClass() );

    if ( ( is_special_node && parent_memory->CurrentChild == BTSpecialChild::NotInitialized ) ||
         ( !is_special_node && parent_memory->CurrentChild != ChildIndex ) )
    {
        // initialize counter if it's first activation
        decorator_memory->RemainingExecutions = FMath::RandRange( MinNumLoops, MaxNumLoops );
        decorator_memory->TimeStarted = GetWorld()->GetTimeSeconds();
    }

    if ( decorator_memory->RemainingExecutions > 0 )
    {
        decorator_memory->RemainingExecutions--;
    }

    const auto should_loop = decorator_memory->RemainingExecutions > 0;

    // set child selection overrides
    if ( should_loop )
    {
        GetParentNode()->SetChildOverride( SearchData, ChildIndex );
    }
}

void UAIExtBTDecorator_RandomLoop::OnBecomeRelevant( UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory )
{
    Super::OnBecomeRelevant( OwnerComp, NodeMemory );

    NumLoops = FMath::RandRange( MinNumLoops, MaxNumLoops );
}
