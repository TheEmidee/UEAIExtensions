#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AIExtStateTreeTaskShowActor.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskShowActorInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskShowActorInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bIsVisible = true;
};

/**
 * Task to show/hide actor
 */
USTRUCT( meta = ( DisplayName = "Show Actor", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskShowActor : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskShowActorInstanceData;

    FAIExtStateTreeTaskShowActor();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskShowActor::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
