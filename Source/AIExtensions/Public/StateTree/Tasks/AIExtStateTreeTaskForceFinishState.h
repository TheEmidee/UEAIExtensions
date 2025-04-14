#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskForceFinishState.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskForceFinishInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskForceFinishInstanceData() = default;

    /** Should the state finish with success?. */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bSucceeded = true;
};

/**
 * Task to force the state to finish
 */
USTRUCT( meta = ( DisplayName = "Force Finish State", Category = "State Tree Tasks|Helpers" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskForceFinish : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskForceFinishInstanceData;

    FAIExtStateTreeTaskForceFinish();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskForceFinish::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}