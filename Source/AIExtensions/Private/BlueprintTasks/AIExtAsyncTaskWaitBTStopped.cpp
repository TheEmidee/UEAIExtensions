#include "BlueprintTasks/AIExtAsyncTaskWaitBTStopped.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

UAIExtAsyncTaskWaitBTStopped::UAIExtAsyncTaskWaitBTStopped()
{
    bCanTick = true;
}

UAIExtAsyncTaskWaitBTStopped * UAIExtAsyncTaskWaitBTStopped::WaitBTStopped( UBehaviorTreeComponent * behavior_tree_component )
{
    auto * task = NewObject< UAIExtAsyncTaskWaitBTStopped >();
    task->BehaviorTreeComponent = behavior_tree_component;
    return task;
}

bool UAIExtAsyncTaskWaitBTStopped::IsTickable() const
{
    return bCanTick;
}

void UAIExtAsyncTaskWaitBTStopped::Tick( float delta_time )
{
    if ( BehaviorTreeComponent == nullptr )
    {
        SetReadyToDestroy();
        return;
    }

    if ( BehaviorTreeComponent->IsRunning() )
    {
        return;
    }

    BroadcastDelegate();
}

TStatId UAIExtAsyncTaskWaitBTStopped::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT( UGBFAsyncTaskWaitBTStopped, STATGROUP_Tickables );
}

void UAIExtAsyncTaskWaitBTStopped::SetReadyToDestroy()
{
    Super::SetReadyToDestroy();
    bCanTick = false;
}

void UAIExtAsyncTaskWaitBTStopped::BroadcastDelegate()
{
    OnBehaviorTreeStoppedDelegate.Broadcast();
    SetReadyToDestroy();
}
