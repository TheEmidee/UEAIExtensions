#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskSetActorLocation.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskSetActorLocationInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSetActorLocationInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FVector Location = FVector::ZeroVector;
};

/**
 * Task to set the location of an actor
 */
USTRUCT( meta = ( DisplayName = "Set Actor Location", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSetActorLocation : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSetActorLocationInstanceData;

    FAIExtStateTreeTaskSetActorLocation();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSetActorLocation::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
