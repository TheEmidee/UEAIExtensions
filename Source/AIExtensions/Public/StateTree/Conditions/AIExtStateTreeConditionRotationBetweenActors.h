#pragma once

#include "AITypes.h"

#include <StateTreeConditionBase.h>

#include "AIExtStateTreeConditionRotationBetweenActors.generated.h"

class USmartObjectSubsystem;

UENUM()
enum class EAIExtStateTreeConditionRotationBetweenActorsAxis : uint8
{
    Roll,
    Pitch,
    Yaw
};

USTRUCT()
struct FAIExtStateTreeConditionRotationBetweenActorsInstanceData
{
    GENERATED_BODY()

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > FirstActor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > SecondActor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    EAIExtStateTreeConditionRotationBetweenActorsAxis Axis = EAIExtStateTreeConditionRotationBetweenActorsAxis::Yaw;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    float DeltaAngleThreshold = 0.0f;
};

STATETREE_POD_INSTANCEDATA( FAIExtStateTreeConditionRotationBetweenActorsInstanceData )

/**
 * Condition to check the delta angle between two actors
 */
USTRUCT( DisplayName = "Rotation Between Actors Compare", Category = "Actors" )
struct FAIExtStateTreeConditionRotationBetweenActors : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeConditionRotationBetweenActorsInstanceData;

    FAIExtStateTreeConditionRotationBetweenActors() = default;

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