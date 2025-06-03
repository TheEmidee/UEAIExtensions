#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskResumeStateTreeLogic.generated.h"

class UStateTreeComponent;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskResumeStateTreeLogicInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskResumeStateTreeLogicInstanceData() = default;

    /** The State Tree component to Resume logic. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< UStateTreeComponent > StateTreeComponent = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FString ResumeReason = FString();
};

/**
 * Task to Resume a state tree component
 */
USTRUCT( meta = ( DisplayName = "Resume State Tree Component", Category = "State Tree Tasks|State Tree" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskResumeStateTreeLogic final : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskResumeStateTreeLogicInstanceData;

    FAIExtStateTreeTaskResumeStateTreeLogic();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskResumeStateTreeLogic::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
