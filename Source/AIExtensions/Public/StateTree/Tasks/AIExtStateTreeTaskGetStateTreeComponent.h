#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskGetStateTreeComponent.generated.h"

class UStateTreeComponent;
class AAIController;
enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetStateTreeComponentInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetStateTreeComponentInstanceData() = default;

    /** The actor to get the state tree component from. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    /** The state tree component of the actor */
    UPROPERTY( EditAnywhere, Category = "Output" )
    TObjectPtr< UStateTreeComponent > StateTreeComponent = nullptr;
};

/**
 * Task to get a state tree component of an actor
 */
USTRUCT( meta = ( DisplayName = "Get State Tree Component", Category = "State Tree Tasks|State Tree" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetStateTreeComponent : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskGetStateTreeComponentInstanceData;

    FAIExtStateTreeTaskGetStateTreeComponent() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetStateTreeComponent::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}