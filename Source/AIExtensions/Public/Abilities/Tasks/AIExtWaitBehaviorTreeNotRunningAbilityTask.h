#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "CoreMinimal.h"

#include "AIExtWaitBehaviorTreeNotRunningAbilityTask.generated.h"

class UBehaviorTreeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIExtOnWaitBehaviorNotRunningDelegate);

UCLASS()
class AIEXTENSIONS_API UAIExtWaitBehaviorTreeNotRunningAbilityTask final : public UAbilityTask
{
    GENERATED_BODY()

public:
    UAIExtWaitBehaviorTreeNotRunningAbilityTask();

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = ( HidePin = "owning_ability", DefaultToSelf = "owning_ability", BlueprintInternalUseOnly = "TRUE" ))
    static UAIExtWaitBehaviorTreeNotRunningAbilityTask* WaitBehaviorTreeNotRunning(UGameplayAbility* owning_ability, UBehaviorTreeComponent* behavior_tree_component);

    void TickTask(float delta_time) override;

private:
    void BroadcastDelegate();

    UPROPERTY(BlueprintAssignable)
    FAIExtOnWaitBehaviorNotRunningDelegate OnBehaviorTreeNotRunning;

    UPROPERTY()
    UBehaviorTreeComponent* BehaviorTreeComponent;
};
