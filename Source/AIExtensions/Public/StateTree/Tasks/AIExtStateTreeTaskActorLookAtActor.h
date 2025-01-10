#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskActorLookAtActor.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskActorLookAtActorInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskActorLookAtActorInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > ActorToRotate = nullptr;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > ActorToLookAt = nullptr;
};

/**
 * Task to orient an actor to another actor
 */
USTRUCT( meta = ( DisplayName = "Actor Look At Actor", Category = "State Tree Tasks|Actors" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskActorLookAtActor : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskActorLookAtActorInstanceData;

    FAIExtStateTreeTaskActorLookAtActor() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskActorLookAtActor::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
