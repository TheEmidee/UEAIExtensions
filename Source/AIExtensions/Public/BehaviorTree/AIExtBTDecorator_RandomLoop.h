#pragma once

#include <BehaviorTree/BTDecorator.h>
#include <CoreMinimal.h>

#include "AIExtBTDecorator_RandomLoop.generated.h"

struct FAIExtBTRandomLoopDecoratorMemory
{
    int32 SearchId;
    uint8 RemainingExecutions;
    float TimeStarted;
};

UCLASS()
class AIEXTENSIONS_API UAIExtBTDecorator_RandomLoop final : public UBTDecorator
{
    GENERATED_BODY()

public:
    UAIExtBTDecorator_RandomLoop();
    
    uint16 GetInstanceMemorySize() const override;
    void DescribeRuntimeValues( const UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray< FString > & Values ) const override;
    FString GetStaticDescription() const override;

#if WITH_EDITOR
    FName GetNodeIconName() const override;
#endif // WITH_EDITOR

protected:
    void OnNodeActivation( FBehaviorTreeSearchData & SearchData ) override;
    void OnBecomeRelevant( UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory ) override;

private:
    UPROPERTY( Category = Decorator, EditAnywhere, meta = ( AllowPrivateAccess = "true", ClampMin = "1" ) )
    int32 MinNumLoops;

    UPROPERTY( Category = Decorator, EditAnywhere, meta = ( AllowPrivateAccess = "true", ClampMin = "1" ) )
    int32 MaxNumLoops;

    int32 NumLoops;
};