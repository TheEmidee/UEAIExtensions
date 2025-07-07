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
    TObjectPtr< AActor > Actor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< AActor > ActorToCopyRotationFrom = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< AActor > ActorToLookAtTo = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FRotator WorldRotation = FRotator::ZeroRotator;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bRotateInstantly = false;

    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( EditCondition = "!bRotateInstantly" ) )
    float RotationSpeed = 1.0f;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bFinishTaskWhenRotationIsComplete = false;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bUpdateYaw = false;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bUpdatePitch = false;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bUpdateRoll = false;

    // Set to true to continue to rotate the actor each tick. Useful if you copy the rotation from another actor, or look at another actor
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bContinuousRotation = false;

    FRotator TargetRotation = FRotator::ZeroRotator;
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

private:
    void UpdateTargetRotation( const FStateTreeExecutionContext & context ) const;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskRotateActor::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
