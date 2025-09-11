#pragma once

#include "CoreMinimal.h"
#include "GameplayCueInterface.h"
#include "StateTreeTaskBase.h"

#include "AIExtStateTreeTaskExecuteBUrstGameplayCue.generated.h"

USTRUCT()
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
USTRUCT( meta = ( DisplayName = "Execute Burst GameplayCue", Category = "State Tree Tasks|GAS" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskExecuteBurstGameplayCue final : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskExecuteBurstGameplayCueInstanceData;

    FAIExtStateTreeTaskExecuteBurstGameplayCue();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskExecuteBurstGameplayCue::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
