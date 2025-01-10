#pragma once

#include <CoreMinimal.h>
#include <GameplayCueInterface.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskExecuteBUrstGameplayCue.generated.h"

USTRUCT( BlueprintType )
struct FAIExtStateTreeTaskExecuteBurstGameplayCueInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskExecuteBurstGameplayCueInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    UPROPERTY( EditAnywhere, Category = "GameplayCue", meta = ( Categories = "GameplayCue" ) )
    FGameplayTag GameplayCueTag;

    UPROPERTY( EditAnywhere, Category = "GameplayCue", meta = ( Categories = "GameplayCue" ) )
    FGameplayCueParameters Parameters;
};

/**
 * Task to execute a gameplay cue on an actor
 */
USTRUCT( meta = ( DisplayName = "Execute Burst GameplayCue", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskExecuteBurstGameplayCue : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskExecuteBurstGameplayCueInstanceData;

    FAIExtStateTreeTaskExecuteBurstGameplayCue() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskExecuteBurstGameplayCue::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
