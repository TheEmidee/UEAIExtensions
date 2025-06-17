#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskSetActorRotation.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskSetActorRotationInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSetActorRotationInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FRotator Rotation;
};

/**
 * Task to set the rotation of an actor
 */
USTRUCT( meta = ( DisplayName = "Set Actor Rotation", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSetActorRotation : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSetActorRotationInstanceData;

    FAIExtStateTreeTaskSetActorRotation();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSetActorRotation::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
