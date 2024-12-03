#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskGetActorLocation.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorLocationInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetActorLocationInstanceData() = default;

    /** The actor to get the location . */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    /** The actor location. */
    UPROPERTY( EditAnywhere, Category = "Output" )
    FVector Location = FVector::ZeroVector;
};

/**
 * Task to get the location of an actor
 */
USTRUCT( meta = ( DisplayName = "Get Actor Location", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorLocation : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskGetActorLocationInstanceData;

    FAIExtStateTreeTaskGetActorLocation() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetActorLocation::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}