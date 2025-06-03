#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskPauseStateTreeLogic.generated.h"

class UStateTreeComponent;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskPauseStateTreeInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskPauseStateTreeInstanceData() = default;

    /** The State Tree component to Pause logic. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< UStateTreeComponent > StateTreeComponent = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FString StopReason = FString();
};

/**
 * Task to Stop a state tree component
 */
USTRUCT( meta = ( DisplayName = "Pause State Tree Component", Category = "State Tree Tasks|State Tree" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskPauseStateTreeLogic final : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskPauseStateTreeInstanceData;

    FAIExtStateTreeTaskPauseStateTreeLogic();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskPauseStateTreeLogic::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
