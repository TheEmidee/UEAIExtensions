#pragma once

#include "Animation/AnimMontage.h"
#include "StateTreeTaskBase.h"

#include "AIExtStateTreeTaskStopMontage.generated.h"

class UAnimInstance;
class UAnimMontage;
enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskStopMontageInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskStopMontageInstanceData() = default;

    /** The skeletal mesh component on which to stop the montage. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< USkeletalMeshComponent > SkeletalMeshComponent = nullptr;

    /** The montage to stop. If not set, will stop any montage being played. */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    TObjectPtr< UAnimMontage > AnimMontage = nullptr;

    /** The blend-out time */
    UPROPERTY( EditAnywhere, Category = "Parameter", meta = ( Optional ) )
    float BlendOutTime = 0.0f;
};

/**
 * Task to stop a montage on a skeletal mesh component
 */
USTRUCT( meta = ( DisplayName = "Stop Montage", Category = "State Tree Tasks|Animation" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskStopMontage : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskStopMontageInstanceData;

    FAIExtStateTreeTaskStopMontage();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskStopMontage::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}