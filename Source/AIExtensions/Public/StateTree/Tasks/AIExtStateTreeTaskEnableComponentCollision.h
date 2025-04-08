#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskEnableComponentCollision.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskEnableComponentCollisionInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskEnableComponentCollisionInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< UPrimitiveComponent > Component = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TEnumAsByte< ECollisionEnabled::Type > NewCollisionType = ECollisionEnabled::NoCollision;
};

/**
 * Task To enable/ disable collision for primitive component
 */
USTRUCT( meta = ( DisplayName = "Enable component Collisions", Category = "State Tree Tasks|Primitive Component" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskEnableComponentCollision : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskEnableComponentCollisionInstanceData;

    FAIExtStateTreeTaskEnableComponentCollision();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskEnableComponentCollision::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
