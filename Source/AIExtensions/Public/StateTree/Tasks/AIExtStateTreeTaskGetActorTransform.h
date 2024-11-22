#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskGetActorTransform.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorTransformInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetActorTransformInstanceData() = default;

    /** The actor to get the location . */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    /** The actor transform. */
    UPROPERTY( EditAnywhere, Category = "Output" )
    FTransform Transform;
};

/**
 * Task to get the location of an actor
 */
USTRUCT( meta = ( DisplayName = "Get Actor Transform", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorTransform : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskGetActorTransformInstanceData;

    FAIExtStateTreeTaskGetActorTransform() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetActorTransform::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}