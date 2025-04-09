#pragma once

#include "AITypes.h"
#include <StateTreeConditionBase.h>

#include "AIExtStateTreeConditionDistanceBetweenActors.generated.h"

class USmartObjectSubsystem;

USTRUCT()
struct FAIExtStateTreeConditionDistanceBetweenActorsInstanceData
{
    GENERATED_BODY()

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > FirstActor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > SecondActor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    float Distance = 0.0f;
};

STATETREE_POD_INSTANCEDATA( FAIExtStateTreeConditionDistanceBetweenActorsInstanceData )

/**
 * Condition to check the distance between two actors
 */
USTRUCT( DisplayName = "Distance Between Actors Compare", Category = "Actors" )
struct FAIExtStateTreeConditionDistanceBetweenActors : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeConditionDistanceBetweenActorsInstanceData;

    FAIExtStateTreeConditionDistanceBetweenActors() = default;

    const UStruct * GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }

    bool TestCondition( FStateTreeExecutionContext & context ) const override;

protected:
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bInvert = false;

    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( InvalidEnumValues = "IsTrue" ) )
    EGenericAICheck Operator = EGenericAICheck::Equal;
};