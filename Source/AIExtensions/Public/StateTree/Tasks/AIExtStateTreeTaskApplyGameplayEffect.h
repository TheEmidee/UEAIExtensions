#pragma once

#include "GameplayEffectTypes.h"
#include "StateTreeTaskBase.h"
#include "Templates/SubclassOf.h"

#include "AIExtStateTreeTaskApplyGameplayEffect.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskApplyGameplayEffectInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskApplyGameplayEffectInstanceData() = default;

    /** The ability system component to use. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< UAbilitySystemComponent > AbilitySystemComponent = nullptr;

    /** The actor on which to find the ability system component if AbilitySystemComponent is not set. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    /** The ability system component to target (optional). If not set, the gameplay effect is applied to AbilitySystemComponent */
    UPROPERTY( EditAnywhere, Category = "Context", meta = ( Optional ) )
    TObjectPtr< UAbilitySystemComponent > TargetAbilitySystemComponent = nullptr;

    /** The actor on which to find the target ability system component if TargetAbilitySystemComponent is not set. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > TargetActor = nullptr;

    /** The ability class to activate */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TSubclassOf< UGameplayEffect > EffectClass = nullptr;

    /** The level of the gameplay effect */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    int Level = 0;

    /** Set to true to remove the gameplay effect when the state exits */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    bool bRemoveEffectWhenTaskExits = false;

    UPROPERTY()
    TObjectPtr< UAbilitySystemComponent > UsedASC;

    FActiveGameplayEffectHandle Handle;
};

/**
 * Task to apply a gameplay effect on an actor
 */
USTRUCT( meta = ( DisplayName = "Apply Gameplay Effect", Category = "State Tree Tasks|GAS" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskApplyGameplayEffect : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskApplyGameplayEffectInstanceData;

    FAIExtStateTreeTaskApplyGameplayEffect();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
    void ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskApplyGameplayEffect::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}