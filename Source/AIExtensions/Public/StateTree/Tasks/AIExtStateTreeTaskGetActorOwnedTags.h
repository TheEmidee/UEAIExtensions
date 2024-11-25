#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskGetActorOwnedTags.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorOwnedTagsInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetActorOwnedTagsInstanceData() = default;

    /** The actor to get the tags from  */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    /** The gameplay tag container with all the tags owned by the actor  */
    UPROPERTY( EditAnywhere, Category = "Output" )
    FGameplayTagContainer OwnedTags;
};

/**
 * Task to get the actors owned tags each tick
 */
USTRUCT( meta = ( DisplayName = "Get Actor Owned Tags", Category = "State Tree Tasks|Helpers" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetActorOwnedTags : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskGetActorOwnedTagsInstanceData;

    FAIExtStateTreeTaskGetActorOwnedTags() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus Tick( FStateTreeExecutionContext & context, const float delta_time ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetActorOwnedTags::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}