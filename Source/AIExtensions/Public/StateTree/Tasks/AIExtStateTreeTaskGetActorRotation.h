#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskGetActorRotation.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorRotationInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetActorRotationInstanceData() = default;

    /** The actor to get the location . */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    /** The actor rotation. */
    UPROPERTY( EditAnywhere, Category = "Output" )
    FRotator Rotation;
};

/**
 * Task to get the location of an actor
 */
USTRUCT( meta = ( DisplayName = "Get Actor Rotation", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorRotation : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskGetActorRotationInstanceData;

    FAIExtStateTreeTaskGetActorRotation() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetActorRotation::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}