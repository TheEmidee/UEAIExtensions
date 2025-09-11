#pragma once

#include "AbilitySystemComponent.h"

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTags.h"
#include "Tasks/AITask.h"

#include "AIExtAITask_ActivateAbility.generated.h"

class UGameplayAbility;

UCLASS()
class AIEXTENSIONS_API UAIExtAITask_ActivateAbility final : public UAITask
{
    GENERATED_BODY()

public:
    explicit UAIExtAITask_ActivateAbility( const FObjectInitializer & object_initializer );

    UFUNCTION( BlueprintCallable, Category = "AI|Tasks", meta = ( DefaultToSelf = "controller", BlueprintInternalUseOnly = "true" ) )
    static UAIExtAITask_ActivateAbility * ActivateAbilityByClass( AAIController * controller, TSubclassOf< UGameplayAbility > ability_class, bool end_when_ability_ends, bool bLockAILogic = true );

    UFUNCTION( BlueprintCallable, Category = "AI|Tasks", meta = ( DefaultToSelf = "controller", BlueprintInternalUseOnly = "true" ) )
    static UAIExtAITask_ActivateAbility * ActivateAbilityByTag( AAIController * controller, FGameplayTag gameplay_tag, bool end_when_ability_ends, bool bLockAILogic = true );

    bool WasActivationSuccessful() const;
    bool DidAbilityEnd() const;

    void Setup( AAIController & ai_controller, UAbilitySystemComponent & asc, bool end_when_ability_ends, TSubclassOf< UGameplayAbility > ability_class );
    void Setup( AAIController & ai_controller, UAbilitySystemComponent & asc, bool end_when_ability_ends, FGameplayTag gameplay_tag );

    void ExternalCancel() override;

private:
    static UAIExtAITask_ActivateAbility * CreateTask( AAIController * controller, bool end_when_ability_ends, bool bLockAILogic );

    bool TryActivateAbilityByHandle( UAbilitySystemComponent & asc, FGameplayAbilitySpecHandle ability_spec_handle );
    void OnGameplayAbilityEnded( UGameplayAbility * ability );

    void Activate() override;
    void OnDestroy( bool bInOwnerFinished ) override;

    TSubclassOf< UGameplayAbility > AbilityClass;
    FGameplayTag AbilityTag;
    FOnGameplayAbilityEnded::FDelegate OnGameplayAbilityEndedDelegate;
    TWeakObjectPtr< UAbilitySystemComponent > ASC;
    FGameplayAbilitySpecHandle AbilitySpecHandle;
    bool bEndsWhenAbilityEnds;
    bool bWasActivationSuccessful;
    bool bDidAbilityEnd;
};

FORCEINLINE bool UAIExtAITask_ActivateAbility::WasActivationSuccessful() const
{
    return bWasActivationSuccessful;
}

FORCEINLINE bool UAIExtAITask_ActivateAbility::DidAbilityEnd() const
{
    return bDidAbilityEnd;
}