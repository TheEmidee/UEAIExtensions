#include "BlueprintTasks/AIExtAsyncWaitBlackboardKeyUpdated.h"

#include <BehaviorTree/BlackboardComponent.h>

UAIExtAsyncWaitBlackboardKeyUpdated * UAIExtAsyncWaitBlackboardKeyUpdated::WaitBBKeyUpdated( UBlackboardComponent * blackboard_component, const FName key_name, const bool only_trigger_once /*= false*/ )
{
    auto * task = NewObject< UAIExtAsyncWaitBlackboardKeyUpdated >();
    task->BlackboardComponent = blackboard_component;
    task->KeyName = key_name;
    task->bOnlyTriggerOnce = only_trigger_once;
    return task;
}

void UAIExtAsyncWaitBlackboardKeyUpdated::Activate()
{
    Super::Activate();

    if ( auto * blackboard_component = BlackboardComponent.Get() )
    {
        const auto key_id = blackboard_component->GetKeyID( KeyName );
        if ( key_id != FBlackboard::InvalidKey )
        {
            const auto observer_delegate = FOnBlackboardChangeNotification::CreateUObject( this, &UAIExtAsyncWaitBlackboardKeyUpdated::OnBlackboardKeyValueChange );
            RegisterObserverDelegateHandle = blackboard_component->RegisterObserver( key_id, this, observer_delegate );
        }
    }
}

void UAIExtAsyncWaitBlackboardKeyUpdated::SetReadyToDestroy()
{
    Super::SetReadyToDestroy();

    if ( BlackboardComponent.IsValid() )
    {
        BlackboardComponent->UnregisterObserversFrom( this );
    }

    BlackboardComponent.Reset();
}

EBlackboardNotificationResult UAIExtAsyncWaitBlackboardKeyUpdated::OnBlackboardKeyValueChange( const UBlackboardComponent & blackboard_component, FBlackboard::FKey changed_key_id )
{
    if ( ShouldBroadcastDelegate() )
    {
        BroadcastDelegate();
        if ( bOnlyTriggerOnce )
        {
            SetReadyToDestroy();
            return EBlackboardNotificationResult::RemoveObserver;
        }
    }

    return EBlackboardNotificationResult::ContinueObserving;
}

bool UAIExtAsyncWaitBlackboardKeyUpdated::ShouldBroadcastDelegate() const
{
    return BlackboardComponent.IsValid();
}

void UAIExtAsyncWaitBlackboardKeyUpdated::BroadcastDelegate() const
{
    OnBlackboardKeyUpdatedDelegate.Broadcast();
}