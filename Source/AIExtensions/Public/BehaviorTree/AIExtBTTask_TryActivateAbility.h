#pragma once

#include "Abilities/GameplayAbility.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CoreMinimal.h"

#include "AIExtBTTask_TryActivateAbility.generated.h"

class UAIExtAITask_ActivateAbility;

struct FAIExtTryActivateAbilityBTTaskMemory
{
    FAIExtTryActivateAbilityBTTaskMemory();

    TWeakObjectPtr< UAIExtAITask_ActivateAbility > Task;
    bool bObserverCanFinishTask;
};

UCLASS( Abstract )
class AIEXTENSIONS_API UAIExtBTTask_TryActivateAbility : public UBTTaskNode
{
    GENERATED_BODY()

public:
    explicit UAIExtBTTask_TryActivateAbility( const FObjectInitializer & object_initializer );

    void InitializeFromAsset( UBehaviorTree & asset ) override;
    EBTNodeResult::Type ExecuteTask( UBehaviorTreeComponent & owner_comp, uint8 * node_memory ) override;
    uint16 GetInstanceMemorySize() const override;
    FString GetStaticDescription() const override;
    void TickTask( UBehaviorTreeComponent & owner_comp, uint8 * node_memory, float delta_seconds ) override;

    void OnGameplayTaskDeactivated( UGameplayTask & task ) override;

protected:
    void OnTaskFinished( UBehaviorTreeComponent & owner_comp, uint8 * node_memory, EBTNodeResult::Type task_result ) override;
    virtual FString GetDetailedStaticDescription() const PURE_VIRTUAL( UGBFBTTask_TryActivateAbility::GetDetailedStaticDescription, return ""; );
    EBTNodeResult::Type AbortTask( UBehaviorTreeComponent & owner_comp, uint8 * node_memory ) override;
    virtual void SetupAITask( UAIExtAITask_ActivateAbility & ai_task, AAIController & ai_controller, UAbilitySystemComponent & asc ) PURE_VIRTUAL( UGBFBTTask_TryActivateAbility::SetupAITask, );
    UAbilitySystemComponent * GetAbilitySystemComponent( UBehaviorTreeComponent & owner_comp ) const;

    // If false, this BT Task when end immediately even if the ability does not end
    // If true, the BT task will end when the ability ends
    UPROPERTY( EditAnywhere, Category = "Target" )
    uint8 bEndWhenAbilityEnds : 1;

private:
    void StartTimer( UBehaviorTreeComponent & owner_comp, uint8 * node_memory );

    UPROPERTY( EditAnywhere, Category = "Target" )
    uint8 bUseActorFromBlackboardKey : 1;

    UPROPERTY( EditAnywhere, Category = "Target", meta = ( EditCondition = "bUseActorFromBlackboardKey" ) )
    FBlackboardKeySelector BlackboardKey;

    UPROPERTY( EditAnywhere, Category = "Task" )
    FBlackboardKeySelector TimeLimitBlackboardKey;

    UPROPERTY( EditAnywhere, Category = "Task" )
    FBlackboardKeySelector DeviationBlackboardKey;
};

UCLASS()
class AIEXTENSIONS_API UAIExtBTTask_TryActivateAbilityByClass final : public UAIExtBTTask_TryActivateAbility
{
    GENERATED_BODY()

public:
    explicit UAIExtBTTask_TryActivateAbilityByClass( const FObjectInitializer & object_initializer );

protected:
    FString GetDetailedStaticDescription() const override;
    void SetupAITask( UAIExtAITask_ActivateAbility & ai_task, AAIController & ai_controller, UAbilitySystemComponent & asc ) override;

private:
    UPROPERTY( Category = "Ability", EditAnywhere )
    TSubclassOf< UGameplayAbility > AbilityClass;
};

/*
 * Try to activate an ability by tag.
 * Note that only the first matching ability will be activated !
 */
UCLASS()
class AIEXTENSIONS_API UAIExtBTTask_TryActivateAbilityByTag final : public UAIExtBTTask_TryActivateAbility
{
    GENERATED_BODY()

public:
    explicit UAIExtBTTask_TryActivateAbilityByTag( const FObjectInitializer & object_initializer );

protected:
    FString GetDetailedStaticDescription() const override;
    void SetupAITask( UAIExtAITask_ActivateAbility & ai_task, AAIController & ai_controller, UAbilitySystemComponent & asc ) override;

private:
    UPROPERTY( Category = "Ability", EditAnywhere )
    FGameplayTag AbilityTag;
};

UENUM()
enum class EAIExtBTTaskSendGameplayEventAssetSource : uint8
{
    None,
    FromBlackboard,
    FromReference
};

USTRUCT()
struct FAIExtBTTaskSendGameplayEventAssetSelector
{
    GENERATED_USTRUCT_BODY()

    FAIExtBTTaskSendGameplayEventAssetSelector();

    UObject * GetAsset( UBehaviorTreeComponent & owner_comp ) const;

    UPROPERTY( EditAnywhere )
    EAIExtBTTaskSendGameplayEventAssetSource AssetSource;

    UPROPERTY( EditAnywhere, meta = ( EditCondition = "AssetSource == EGBFBTTaskSendGameplayEventAssetSource::FromBlackboard" ) )
    FBlackboardKeySelector BlackboardKey;

    UPROPERTY( EditAnywhere, meta = ( EditCondition = "AssetSource == EGBFBTTaskSendGameplayEventAssetSource::FromReference" ) )
    UObject * Asset;
};

UCLASS()
class AIEXTENSIONS_API UAIExtBTTask_SendGameplayEvent final : public UAIExtBTTask_TryActivateAbility
{
    GENERATED_BODY()

public:
    explicit UAIExtBTTask_SendGameplayEvent( const FObjectInitializer & object_initializer );

    EBTNodeResult::Type ExecuteTask( UBehaviorTreeComponent & owner_comp, uint8 * node_memory ) override;
    FString GetDetailedStaticDescription() const override;

private:
    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    FGameplayTag TriggerTag;

    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    FAIExtBTTaskSendGameplayEventAssetSelector Instigator;

    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    FAIExtBTTaskSendGameplayEventAssetSelector Target;

    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    FAIExtBTTaskSendGameplayEventAssetSelector OptionalObject1;

    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    FAIExtBTTaskSendGameplayEventAssetSelector OptionalObject2;

    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    FGameplayTagContainer InstigatorTags;

    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    FGameplayTagContainer TargetTags;

    UPROPERTY( EditAnywhere, Category = "Payload Data" )
    float EventMagnitude;

    FGameplayEventData Payload;
};