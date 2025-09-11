#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "AIExtStateTreeTaskSendGameplayEvent.generated.h"

class UAbilitySystemComponent;
class UStateTreeComponent;

USTRUCT()
struct FAIExtStateTreeTaskSendGameplayEventInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSendGameplayEventInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< AActor > Target = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< UAbilitySystemComponent > TargetASC = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FGameplayTag EventTag;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    float PayloadEventMagnitude = 0.0f;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< AActor > PayloadInstigator = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FGameplayTagContainer PayloadInstigatorTags;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< AActor > PayloadTarget = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FGameplayTagContainer PayloadTargetTags;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< UObject > PayloadOptionalObject = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< UObject > PayloadOptionalObject2 = nullptr;
};

/**
 * Task to send a gameplay event to an actor or an ability system component
 */
USTRUCT( meta = ( DisplayName = "Send Gameplay Event", Category = "State Tree Tasks|GAS" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSendGameplayEvent : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSendGameplayEventInstanceData;

    FAIExtStateTreeTaskSendGameplayEvent();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSendGameplayEvent::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
