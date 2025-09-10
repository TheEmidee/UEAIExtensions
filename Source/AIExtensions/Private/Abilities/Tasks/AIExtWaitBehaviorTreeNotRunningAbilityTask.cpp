#include "Abilities/Tasks/AIExtWaitBehaviorTreeNotRunningAbilityTask.h"
#include <BehaviorTree/BehaviorTreeComponent.h>

UAIExtWaitBehaviorTreeNotRunningAbilityTask::UAIExtWaitBehaviorTreeNotRunningAbilityTask()
{
    bTickingTask = true;
    BehaviorTreeComponent = nullptr;
}

UAIExtWaitBehaviorTreeNotRunningAbilityTask* UAIExtWaitBehaviorTreeNotRunningAbilityTask::WaitBehaviorTreeNotRunning(UGameplayAbility* owning_ability, UBehaviorTreeComponent* behavior_tree_component)
{
    auto* task = NewAbilityTask<UAIExtWaitBehaviorTreeNotRunningAbilityTask>(owning_ability);
    task->BehaviorTreeComponent = behavior_tree_component;
    return task;
}

void UAIExtWaitBehaviorTreeNotRunningAbilityTask::TickTask(float delta_time)
{
    Super::TickTask(delta_time);

    if (!IsValid(BehaviorTreeComponent) || !BehaviorTreeComponent->IsRunning())
    {
        BroadcastDelegate();
    }
}

void UAIExtWaitBehaviorTreeNotRunningAbilityTask::BroadcastDelegate()
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnBehaviorTreeNotRunning.Broadcast();
        EndTask();
    }
}
