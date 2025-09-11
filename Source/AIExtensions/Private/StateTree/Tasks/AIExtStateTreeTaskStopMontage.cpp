#include "StateTree/Tasks/AIExtStateTreeTaskStopMontage.h"

#include "VisualLogger/VisualLogger.h"

#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "StateTreeExecutionContext.h"

FAIExtStateTreeTaskStopMontage::FAIExtStateTreeTaskStopMontage()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

inline EStateTreeRunStatus FAIExtStateTreeTaskStopMontage::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.SkeletalMeshComponent == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskStopMontage failed because the skeletal mesh component is not set." ) );
        return EStateTreeRunStatus::Failed;
    }

    auto * anim_instance = instance_data.SkeletalMeshComponent->GetAnimInstance();

    if ( anim_instance == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskStopMontage failed because there's no anim instance on the skeletal mesh component." ) );
        return EStateTreeRunStatus::Failed;
    }

    UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskStopMontage stopped montage." ) );
    anim_instance->Montage_Stop( instance_data.BlendOutTime, instance_data.AnimMontage );

    return EStateTreeRunStatus::Running;
}