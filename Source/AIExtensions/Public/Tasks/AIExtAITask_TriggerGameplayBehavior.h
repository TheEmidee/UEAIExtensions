#pragma once

#include <CoreMinimal.h>
#include <Tasks/AITask.h>

#include "AIExtAITask_TriggerGameplayBehavior.generated.h"

class UGameplayBehavior;

UCLASS()
class AIEXTENSIONS_API UAIExtAITask_TriggerGameplayBehavior final : public UAITask
{
    GENERATED_BODY()

public:
    explicit UAIExtAITask_TriggerGameplayBehavior( const FObjectInitializer & object_initializer );

    UFUNCTION( BlueprintCallable, Category = "AI|Tasks", meta = ( DefaultToSelf = "controller", BlueprintInternalUseOnly = "true" ) )
    static UAIExtAITask_TriggerGameplayBehavior * TriggerGameplayBehavior( AAIController * controller, UGameplayBehaviorConfig * gameplay_behavior_config, bool lock_ai_logic = true, AActor * gameplay_behavior_owner = nullptr );

    UFUNCTION( BlueprintCallable, Category = "AI|Tasks", DisplayName = "Trigger Gameplay Behavior With Data Asset", meta = ( DefaultToSelf = "controller", BlueprintInternalUseOnly = "true" ) )
    static UAIExtAITask_TriggerGameplayBehavior * TriggerGameplayBehaviorWithDataAsset( AAIController * controller, UAIExtGameplayBehaviorDataAsset * gameplay_behavior_data_asset, bool lock_ai_logic = true, AActor * gameplay_behavior_owner = nullptr );

protected:
    void OnDestroy( bool bInOwnerFinished ) override;
    void Activate() override;

private:
    void Abort();
    void OnGameplayBehaviorFinished( UGameplayBehavior & behavior, AActor & avatar, const bool interrupted );

    UPROPERTY( BlueprintAssignable )
    FGenericGameplayTaskDelegate OnSucceeded;

    UPROPERTY( BlueprintAssignable )
    FGenericGameplayTaskDelegate OnFailed;

    UPROPERTY()
    TObjectPtr< UGameplayBehaviorConfig > GameplayBehaviorConfig;

    UPROPERTY()
    TObjectPtr< UGameplayBehavior > GameplayBehavior;

    UPROPERTY()
    TObjectPtr< AActor > GameplayBehaviorOwner;

    FDelegateHandle OnBehaviorFinishedNotifyHandle;
    bool bBehaviorFinished;
};