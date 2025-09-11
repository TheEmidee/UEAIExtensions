#pragma once

#include "AITypes.h"

#include "StateTreeConditionBase.h"

#include "AIExtStateTreeConditionDistanceXY.generated.h"

USTRUCT()
struct FAIExtStateTreeConditionDistanceXYInstanceData
{
    GENERATED_BODY()

    UPROPERTY( EditAnywhere, Category = "Context" )
    FVector Source = FVector( EForceInit::ForceInitToZero );

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FVector Target = FVector( EForceInit::ForceInitToZero );

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    float Distance = 0.0f;
};

STATETREE_POD_INSTANCEDATA( FAIExtStateTreeConditionDistanceXYInstanceData )

USTRUCT( DisplayName = "Distance XY Compare", Category = "Vectors" )
struct FAIExtStateTreeConditionDistanceXY : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeConditionDistanceXYInstanceData;

    FAIExtStateTreeConditionDistanceXY() = default;

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