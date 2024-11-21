#pragma once

#include <Animation/AnimMontage.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreePlayMontageTask.generated.h"

class UAnimInstance;
class UAnimMontage;
enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreePlayMontageTaskInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreePlayMontageTaskInstanceData() = default;

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
};

/**
 * Task to play a montage on a skeletal mesh component
 */
USTRUCT( meta = ( DisplayName = "Play Montage" ) )
struct AIEXTENSIONS_API FAIExtStateTreePlayMontageTask : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreePlayMontageTaskInstanceData;

    FAIExtStateTreePlayMontageTask();

    const UStruct * GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
    void ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;

private:
    UFUNCTION()
    void OnMontageBlendingOut( UAnimMontage * montage, bool interrupted );

    UFUNCTION()
    void OnMontageEnded( UAnimMontage * montage, bool interrupted );

    mutable TWeakObjectPtr< UAnimInstance > AnimInstance;
    mutable FOnMontageBlendingOutStarted BlendingOutDelegate;
    mutable FOnMontageEnded MontageEndedDelegate;
};