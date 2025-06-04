#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskEnableAnimation.generated.h"

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskSetAnimationModeInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSetAnimationModeInstanceData() = default;

    /** The Skeletal Mesh Component to Set the animation mode on. */
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< USkeletalMeshComponent > SkeletalMeshComponent = nullptr;

    /** new animation mode */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TEnumAsByte< EAnimationMode::Type > AnimationMode;
};

/**
 * Task to stop / resume animation of a skeletal mesh
 */

USTRUCT( meta = ( DisplayName = "Set SkeletalMesh Animation Mode", Category = "State Tree Tasks|Animation" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskEnableAnimation final : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSetAnimationModeInstanceData;

    FAIExtStateTreeTaskEnableAnimation();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskEnableAnimation::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}