#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Tickable.h"

#include "AIExtAsyncTaskWaitBTStopped.generated.h"

class UBehaviorTreeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FAIExtOnBehaviorTreeStoppedDelegate );

UCLASS()
class AIEXTENSIONS_API UAIExtAsyncTaskWaitBTStopped final : public UBlueprintAsyncActionBase, public FTickableGameObject
{
    GENERATED_BODY()

public:
    UAIExtAsyncTaskWaitBTStopped();

    UFUNCTION( BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true", Category = "AI", WorldContext = "WorldContextObject" ) )
    static UAIExtAsyncTaskWaitBTStopped * WaitBTStopped( UBehaviorTreeComponent * behavior_tree_component );

    bool IsTickable() const override;
    void Tick( float delta_time ) override;
    TStatId GetStatId() const override;

    void SetReadyToDestroy() override;

private:
    void BroadcastDelegate();

    UPROPERTY()
    TWeakObjectPtr< UBehaviorTreeComponent > BehaviorTreeComponent;

    UPROPERTY( BlueprintAssignable )
    FAIExtOnBehaviorTreeStoppedDelegate OnBehaviorTreeStoppedDelegate;

    bool bCanTick;
};
