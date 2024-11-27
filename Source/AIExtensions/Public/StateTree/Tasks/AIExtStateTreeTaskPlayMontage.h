#pragma once

#include <Animation/AnimMontage.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskPlayMontage.generated.h"

class UAnimInstance;
class UAnimMontage;
enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

UCLASS()
class AIEXTENSIONS_API UAIExtStateTreeTaskPlayMontageInstanceData : public UObject
{
    GENERATED_BODY()

public:
    UAIExtStateTreeTaskPlayMontageInstanceData() = default;

    EStateTreeRunStatus OnEnterState( const FStateTreeExecutionContext & context );
    EStateTreeRunStatus OnTick( const FStateTreeExecutionContext & context, float delta_time );
    void OnExitState();

private:
    void Cleanup();

    UFUNCTION()
    void OnMontageBlendingOut( UAnimMontage * montage, bool interrupted );

    /** The skeletal mesh component on which to play the montage. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< USkeletalMeshComponent > SkeletalMeshComponent = nullptr;

    /** The montage to play */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< UAnimMontage > AnimMontage = nullptr;

    /** The play rate of the montage */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    float PlayRate = 1.0f;

    /** The starting position in the montage */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    float StartingPosition = 0.0f;

    /** The starting section in the montage */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    FName StartingSection = NAME_None;

    /** The starting section in the montage */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    bool bEndTaskWhenMontageEnds = false;

    /** The starting section in the montage */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional, EditCondition = "bEndTaskWhenMontageEnds" ) )
    bool bFailTaskWhenMontageIsInterrupted = true;

    /** The starting section in the montage */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    bool bStopMontageWhenTaskEnds = false;

    /** The blend out to use when stopping the montage when the task ends */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional, EditCondition = "bStopMontageWhenTaskEnds" ) )
    float MontageStopBlendOutTime = 0.0f;

    TWeakObjectPtr< UAnimInstance > AnimInstance;
    FOnMontageBlendingOutStarted BlendingOutDelegate;
    EStateTreeRunStatus RunStatus;
};

/**
 * Task to play a montage on a skeletal mesh component
 */
USTRUCT( meta = ( DisplayName = "Play Montage", Category = "State Tree Tasks|Animation" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskPlayMontage : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using UInstanceDataType = UAIExtStateTreeTaskPlayMontageInstanceData;

    FAIExtStateTreeTaskPlayMontage() = default;

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
    EStateTreeRunStatus Tick( FStateTreeExecutionContext & context, const float delta_time ) const override;
    void ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskPlayMontage::GetInstanceDataType() const
{
    return UInstanceDataType::StaticClass();
}