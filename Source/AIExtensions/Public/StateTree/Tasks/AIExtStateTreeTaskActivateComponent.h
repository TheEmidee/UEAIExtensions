#pragma once

#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskActivateComponent.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskActivateComponentInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskActivateComponentInstanceData() = default;

    /** The component to (de)activate. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< UActorComponent > Component = nullptr;

    /** Whether to enable the component or not. */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bActivate = true;

    /** Whether to reset the component if it is activated. */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bResetOnActivate = true;
};

/**
 * Task to activate or deactivate an actor component
 */
USTRUCT( meta = ( DisplayName = "Activate Actor Component", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskActivateComponent : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskActivateComponentInstanceData;

    FAIExtStateTreeTaskActivateComponent();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskActivateComponent::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}