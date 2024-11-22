#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskGetAIController.generated.h"

class AAIController;
enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetAIControllerInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetAIControllerInstanceData() = default;

    /** The pawn to get the AI Controller from. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< APawn > Pawn = nullptr;

    /** The AI Controller of the pawn */
    UPROPERTY( EditAnywhere, Category = "Output" )
    TObjectPtr< AAIController > AIController = nullptr;
};

/**
 * Task to get the AI Controller of a pawn
 */
USTRUCT( meta = ( DisplayName = "Get AI Controller", Category = "State Tree Tasks|Pawn" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetAIController : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskGetAIControllerInstanceData;

    FAIExtStateTreeTaskGetAIController() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetAIController::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}