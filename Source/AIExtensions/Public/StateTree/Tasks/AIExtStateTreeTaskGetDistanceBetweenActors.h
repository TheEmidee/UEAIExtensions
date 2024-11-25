#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskGetDistanceBetweenActors.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetDistanceBetweenActorsInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetDistanceBetweenActorsInstanceData() = default;

    /** The first actor  */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor1 = nullptr;

    /** The second actor  */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor2 = nullptr;

    /** The distance between the actors  */
    UPROPERTY( EditAnywhere, Category = "Output" )
    float Distance;
};

/**
 * Task to get the actors owned tags each tick
 */
USTRUCT( meta = ( DisplayName = "Get Distance Between Actors", Category = "State Tree Tasks|Actors" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetDistanceBetweenActors : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskGetDistanceBetweenActorsInstanceData;

    FAIExtStateTreeTaskGetDistanceBetweenActors() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus Tick( FStateTreeExecutionContext & context, const float delta_time ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetDistanceBetweenActors::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}