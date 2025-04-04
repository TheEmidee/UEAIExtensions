#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskRotateActor.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskRotateActorInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskRotateActorInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > ActorToRotate = nullptr;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > ActorToCopyRotationFrom = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FRotator WorldRotation;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    float RotationSpeed = 1.0f;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bFinishTaskWhenRotationIsComplete = false;

    FRotator TargetRotation;
};

/**
 * Task to rotate an actor over time
 */
USTRUCT( meta = ( DisplayName = "Rotate Actor", Category = "State Tree Tasks|Actors" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskRotateActor final : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskRotateActorInstanceData;

    FAIExtStateTreeTaskRotateActor() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
    EStateTreeRunStatus Tick( FStateTreeExecutionContext & context, const float delta_time ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskRotateActor::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
