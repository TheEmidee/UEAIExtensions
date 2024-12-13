#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskSendStateTreeEvent.generated.h"

class UStateTreeComponent;

USTRUCT()
struct FAIExtStateTreeTaskSendStateTreeEventInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSendStateTreeEventInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< UStateTreeComponent > StateTreeComponent = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FGameplayTag EventTag;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FInstancedStruct Payload;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FName Origin;
};

/**
 * Task to send event to state tree
 */
USTRUCT( meta = ( DisplayName = "Send State Tree Event", Category = "State Tree Tasks|State Tree" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSendStateTreeEvent : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSendStateTreeEventInstanceData;

    FAIExtStateTreeTaskSendStateTreeEvent() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSendStateTreeEvent::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
