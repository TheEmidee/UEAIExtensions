#pragma once

#include <GameplayAbilitySpecHandle.h>
#include <StateTreeTaskBase.h>
#include <Templates/SubclassOf.h>

#include "AIExtStateTreeTaskActivateAbility.generated.h"

struct FAbilityEndedData;
class UGameplayAbility;
class UAbilitySystemComponent;
enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

UCLASS()
class AIEXTENSIONS_API UAIExtStateTreeTaskActivateAbilityInstanceData : public UObject
{
    GENERATED_BODY()

public:
    UAIExtStateTreeTaskActivateAbilityInstanceData() = default;

    void OnAbilityEnded( const FAbilityEndedData & ability_ended_data );

    /** The ability system component on which to activate the ability. */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< UAbilitySystemComponent > AbilitySystemComponent = nullptr;

    /** The actor on which to activate the ability. This is used if nothing is bound to the AbilitySystemComponent property. */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< AActor > Actor = nullptr;

    /** The ability class to activate */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TSubclassOf< UGameplayAbility > AbilityClass = nullptr;

    /** Set to true to give the ability before activating it */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    bool bGiveAbility = false;

    /** Set to true to remove the ability after it has finished to execute */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional, EditCondition = "bGiveAbility" ) )
    bool bRemoveAbility = true;

    /** Set to true to end the task when the ability ends (successfully or cancelled */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    bool bEndTaskWhenAbilityEnds = false;

    /** Set to true to end the ability when the task exits */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    bool bEndAbilityWhenTaskExits = false;

    FGameplayAbilitySpecHandle AbilitySpecHandle;
    EStateTreeRunStatus RunStatus = EStateTreeRunStatus::Running;
};

/**
 * Task to activate an ability on an ability system component or an actor
 */
USTRUCT( meta = ( DisplayName = "Activate Ability", Category = "State Tree Tasks|GAS" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskActivateAbility : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using UInstanceDataType = UAIExtStateTreeTaskActivateAbilityInstanceData;

    FAIExtStateTreeTaskActivateAbility() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
    EStateTreeRunStatus Tick( FStateTreeExecutionContext & context, const float delta_time ) const override;
    void ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskActivateAbility::GetInstanceDataType() const
{
    return UInstanceDataType::StaticClass();
}