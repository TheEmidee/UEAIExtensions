#pragma once

#include "StateTreeTaskBase.h"

#include "AIExtStateTreeTaskHasMatchingGameplayTags.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskHasMatchingGameplayTagInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskHasMatchingGameplayTagInstanceData() = default;

    /** Container to check for the tag. */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FGameplayTagContainer TagContainer;

    /** Tag to check for in the container. */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FGameplayTagContainer OtherTagContainer;

    UPROPERTY( EditAnywhere, Category = "Output" )
    uint8 bHasTag : 1;
};

USTRUCT( meta = ( DisplayName = "Has Matching Gameplay Tags", Category = "State Tree Tasks|Gameplay Tags" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskHasMatchingGameplayTags : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskHasMatchingGameplayTagInstanceData;

    FAIExtStateTreeTaskHasMatchingGameplayTags();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus Tick( FStateTreeExecutionContext & context, const float delta_time ) const override;

    UPROPERTY( EditAnywhere, Category = "Condition" )
    EGameplayContainerMatchType MatchType = EGameplayContainerMatchType::Any;

    /** If true, the tag has to be exactly present, if false then TagContainer will include it's parent tags while matching */
    UPROPERTY( EditAnywhere, Category = "Condition" )
    bool bExactMatch = false;

    UPROPERTY( EditAnywhere, Category = "Condition" )
    bool bInvert = false;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskHasMatchingGameplayTags::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
