#include "StateTree/Tasks/AIExtStateTreePlayMontageTask.h"

#include <Animation/AnimInstance.h>
#include <Components/SkeletalMeshComponent.h>
#include <StateTreeExecutionContext.h>

EStateTreeRunStatus UAIExtStateTreePlayMontageTaskInstanceData::OnEnterState( const FStateTreeExecutionContext & context )
{
    if ( SkeletalMeshComponent == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    if ( AnimMontage == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    auto * anim_instance = SkeletalMeshComponent->GetAnimInstance();

    if ( anim_instance == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    AnimInstance = anim_instance;

    const auto montage_length = AnimInstance->Montage_Play( AnimMontage, PlayRate, EMontagePlayReturnType::MontageLength, StartingPosition );

    if ( montage_length == 0.0f )
    {
        return EStateTreeRunStatus::Failed;
    }

    if ( StartingSection != NAME_None )
    {
        AnimInstance->Montage_JumpToSection( StartingSection, AnimMontage );
    }

    if ( bEndTaskWhenMontageEnds )
    {
        AnimInstance->OnMontageBlendingOut.AddUniqueDynamic( this, &ThisClass::OnMontageBlendingOut );
    }

    RunStatus = EStateTreeRunStatus::Running;
    return RunStatus;
}

EStateTreeRunStatus UAIExtStateTreePlayMontageTaskInstanceData::OnTick( const FStateTreeExecutionContext & context, float delta_time )
{
    return RunStatus;
}

void UAIExtStateTreePlayMontageTaskInstanceData::OnExitState()
{
    Cleanup();

    if ( bStopMontageWhenTaskEnds && AnimInstance.IsValid() )
    {
        AnimInstance->Montage_Stop( MontageStopBlendOutTime, AnimMontage );
    }
}

void UAIExtStateTreePlayMontageTaskInstanceData::Cleanup()
{
    if ( AnimInstance != nullptr )
    {
        AnimInstance->OnMontageBlendingOut.RemoveDynamic( this, &ThisClass::OnMontageBlendingOut );
    }
}

void UAIExtStateTreePlayMontageTaskInstanceData::OnMontageBlendingOut( UAnimMontage * montage, bool interrupted )
{
    if ( montage == AnimMontage )
    {
        RunStatus = ( bFailTaskWhenMontageIsInterrupted && interrupted ) ? EStateTreeRunStatus::Failed : EStateTreeRunStatus::Succeeded;
    }
}

FAIExtStateTreePlayMontageTask::FAIExtStateTreePlayMontageTask()
{
}

EStateTreeRunStatus FAIExtStateTreePlayMontageTask::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto * instance_data = context.GetInstanceDataPtr< UInstanceDataType >( *this );

    check( instance_data != nullptr );

    return instance_data->OnEnterState( context );
}

EStateTreeRunStatus FAIExtStateTreePlayMontageTask::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    auto * instance_data = context.GetInstanceDataPtr< UInstanceDataType >( *this );

    check( instance_data != nullptr );

    return instance_data->OnTick( context, delta_time );
}

void FAIExtStateTreePlayMontageTask::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto * instance_data = context.GetInstanceDataPtr< UInstanceDataType >( *this );

    check( instance_data != nullptr );

    instance_data->OnExitState();
}