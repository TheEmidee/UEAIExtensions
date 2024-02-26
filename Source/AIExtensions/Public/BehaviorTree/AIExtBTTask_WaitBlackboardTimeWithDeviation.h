#pragma once

#include <BehaviorTree/Tasks/BTTask_Wait.h>
#include <CoreMinimal.h>

#include "AIExtBTTask_WaitBlackboardTimeWithDeviation.generated.h"

UCLASS( hidecategories = Wait )
class AIEXTENSIONS_API UAIExtBTTask_WaitBlackboardTimeWithDeviation : public UBTTask_Wait
{
    GENERATED_BODY()

public:
    void InitializeFromAsset( UBehaviorTree & asset ) override;
    FString GetStaticDescription() const override;
    EBTNodeResult::Type ExecuteTask( UBehaviorTreeComponent & owner_comp, uint8 * node_memory ) override;

private:
    UPROPERTY( EditAnywhere, Category = Blackboard )
    FBlackboardKeySelector TimeBlackboardKey;

    UPROPERTY( EditAnywhere, Category = Blackboard )
    FBlackboardKeySelector DeviationBlackboardKey;
};
