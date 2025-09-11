#include "StateTree/Tasks/AIExtStateTreeTaskPlayMontage.h"

#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "StateTreeExecutionContext.h"
#include "VisualLogger/VisualLogger.h"

EStateTreeRunStatus UAIExtStateTreeTaskPlayMontageInstanceData::OnEnterState( const FStateTreeExecutionContext & context )
{
    if ( SkeletalMeshComponent == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskPlayMontage failed because no skeletal mesh component is set." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( AnimMontage == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskPlayMontage failed because no anim montage is set." ) );
        return EStateTreeRunStatus::Failed;
    }

    auto * anim_instance = SkeletalMeshComponent->GetAnimInstance();

    if ( anim_instance == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskPlayMontage failed because there's no anim instance on the skeletal mesh." ) );
        return EStateTreeRunStatus::Failed;
    }

    AnimInstance = anim_instance;

    const auto montage_length = AnimInstance->Montage_Play( AnimMontage, PlayRate, EMontagePlayReturnType::MontageLength, StartingPosition );

    if ( montage_length == 0.0f )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskPlayMontage failed because the montage could not be played." ) );
        return EStateTreeRunStatus::Failed;
    }

    UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskPlayMontage played montage." ) );

    if ( StartingSection != NAME_None )
    {
        AnimInstance->Montage_JumpToSection( StartingSection, AnimMontage );
        UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskPlayMontage jumped to section %s." ), *StartingSection.ToString() );
    }

    if ( bEndTaskWhenMontageEnds )
    {
        AnimInstance->OnMontageBlendingOut.AddUniqueDynamic( this, &ThisClass::OnMontageBlendingOut );
    }

    RunStatus = EStateTreeRunStatus::Running;
    return RunStatus;
}

EStateTreeRunStatus UAIExtStateTreeTaskPlayMontageInstanceData::OnTick( const FStateTreeExecutionContext & context, float delta_time )
{
    return RunStatus;
}

void UAIExtStateTreeTaskPlayMontageInstanceData::OnExitState()
{
    Cleanup();

    if ( bStopMontageWhenTaskEnds && AnimInstance.IsValid() )
    {
        AnimInstance->Montage_Stop( MontageStopBlendOutTime, AnimMontage );
    }
}

void UAIExtStateTreeTaskPlayMontageInstanceData::Cleanup()
{
    if ( AnimInstance != nullptr )
    {
        AnimInstance->OnMontageBlendingOut.RemoveDynamic( this, &ThisClass::OnMontageBlendingOut );
    }
}

void UAIExtStateTreeTaskPlayMontageInstanceData::OnMontageBlendingOut( UAnimMontage * montage, bool interrupted )
{
    if ( montage == AnimMontage )
    {
        RunStatus = ( bFailTaskWhenMontageIsInterrupted && interrupted ) ? EStateTreeRunStatus::Failed : EStateTreeRunStatus::Succeeded;
    }
}

EStateTreeRunStatus FAIExtStateTreeTaskPlayMontage::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto * instance_data = context.GetInstanceDataPtr< UInstanceDataType >( *this );

    check( instance_data != nullptr );

    return instance_data->OnEnterState( context );
}

EStateTreeRunStatus FAIExtStateTreeTaskPlayMontage::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    auto * instance_data = context.GetInstanceDataPtr< UInstanceDataType >( *this );

    check( instance_data != nullptr );

    return instance_data->OnTick( context, delta_time );
}

void FAIExtStateTreeTaskPlayMontage::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto * instance_data = context.GetInstanceDataPtr< UInstanceDataType >( *this );

    check( instance_data != nullptr );

    instance_data->OnExitState();
}