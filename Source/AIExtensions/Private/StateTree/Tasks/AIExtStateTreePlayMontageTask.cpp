#include "StateTree/Tasks/AIExtStateTreePlayMontageTask.h"

#include "Animation/AnimInstance.h"

#include <Components/SkeletalMeshComponent.h>
#include <StateTreeExecutionContext.h>

FAIExtStateTreePlayMontageTask::FAIExtStateTreePlayMontageTask()
{
    bShouldCallTick = false;
}

EStateTreeRunStatus FAIExtStateTreePlayMontageTask::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    FInstanceDataType & instance_data = context.GetInstanceData( *this );

    if ( instance_data.SkeletalMeshComponent == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.AnimMontage == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    auto * anim_instance = instance_data.SkeletalMeshComponent->GetAnimInstance();

    if ( anim_instance == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    const auto montage_length = anim_instance->Montage_Play( instance_data.AnimMontage, instance_data.PlayRate, EMontagePlayReturnType::MontageLength, instance_data.StartingPosition );

    if ( montage_length == 0.0f )
    {
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.StartingSection != NAME_None )
    {
        anim_instance->Montage_JumpToSection( instance_data.StartingSection, instance_data.AnimMontage );
    }

    if ( instance_data.bEndTaskWhenMontageEnds )
    {
        BlendingOutDelegate.BindUObject( this, &FAIExtStateTreePlayMontageTask::OnMontageBlendingOut );
        anim_instance->Montage_SetBlendingOutDelegate( BlendingOutDelegate, instance_data.AnimMontage );

        MontageEndedDelegate.BindUObject( this, &FAIExtStateTreePlayMontageTask::OnMontageEnded );
        anim_instance->Montage_SetEndDelegate( MontageEndedDelegate, instance_data.AnimMontage );
    }

    return EStateTreeRunStatus::Running;
}

void FAIExtStateTreePlayMontageTask::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    BlendingOutDelegate.Unbind();
    MontageEndedDelegate.Unbind();

    FInstanceDataType & instance_data = context.GetInstanceData( *this );

    if ( !instance_data.bStopMontageWhenTaskEnds )
    {
        return;
    }

    if ( AnimInstance.IsValid() )
    {
        AnimInstance->Montage_Stop( instance_data.MontageStopBlendOutTime, instance_data.AnimMontage );
    }
}

void FAIExtStateTreePlayMontageTask::OnMontageBlendingOut( UAnimMontage * montage, bool interrupted )
{
    RunStatus =
        // check UStateTreeTask_PlayContextualAnim_InstanceData
}

void FAIExtStateTreePlayMontageTask::OnMontageEnded( UAnimMontage * montage, bool interrupted )
{
}