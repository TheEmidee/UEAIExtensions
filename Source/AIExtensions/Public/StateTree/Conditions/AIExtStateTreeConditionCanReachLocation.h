#pragma once

#include "CoreMinimal.h"
#include "StateTreeConditionBase.h"

#include "AIExtStateTreeConditionCanReachLocation.generated.h"

class AAIController;

USTRUCT()
struct FAIExtStateTreeConditionCanReachLocationInstanceData
{
    GENERATED_BODY()

    UPROPERTY( EditAnywhere, Category = "Input" )
    FVector Location = FVector::ZeroVector;
};

/**
 * Condition to check if a Location is valid for AI Controller.
 */
USTRUCT( DisplayName = "Can Reach Location", Category = "AI Controller" )
struct FAIExtStateTreeConditionCanReachLocation : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    FAIExtStateTreeConditionCanReachLocation() = default;

    const UStruct * GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }

    using FInstanceDataType = FAIExtStateTreeConditionCanReachLocationInstanceData;

    bool TestCondition( FStateTreeExecutionContext & context ) const override;
};
