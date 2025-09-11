#include "StateTree/Tasks/AIExtStateTreeTaskRotateActor.h"

#include "Kismet/KismetMathLibrary.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FAIExtStateTreeTaskRotateActor::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Actor == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskRotateActor can't rotate the actor because it's null." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( !instance_data.bContinuousRotation )
    {
        UpdateTargetRotation( context );
    }

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAIExtStateTreeTaskRotateActor::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    const auto current_rotation = instance_data.Actor->GetActorRotation();

    if ( instance_data.bContinuousRotation )
    {
        UpdateTargetRotation( context );
    }

    if ( instance_data.bRotateInstantly )
    {
        const auto new_rotation = FRotator(
            instance_data.bUpdatePitch ? instance_data.TargetRotation.Pitch : current_rotation.Pitch,
            instance_data.bUpdateYaw ? instance_data.TargetRotation.Yaw : current_rotation.Yaw,
            instance_data.bUpdateRoll ? instance_data.TargetRotation.Roll : current_rotation.Roll );

        instance_data.Actor->SetActorRotation( new_rotation );

        if ( instance_data.bFinishTaskWhenRotationIsComplete )
        {
            return EStateTreeRunStatus::Succeeded;
        }

        return EStateTreeRunStatus::Running;
    }

    auto rotation = FMath::RInterpConstantTo( current_rotation, instance_data.TargetRotation, delta_time, instance_data.RotationSpeed );
    auto rotation_matches = true;

    if ( !instance_data.bUpdatePitch )
    {
        rotation.Pitch = current_rotation.Pitch;
    }
    else
    {
        rotation_matches &= FMath::IsNearlyEqual( rotation.Pitch, instance_data.TargetRotation.Pitch, 0.01f );
    }

    if ( !instance_data.bUpdateYaw )
    {
        rotation.Yaw = current_rotation.Yaw;
    }
    else
    {
        rotation_matches &= FMath::IsNearlyEqual( rotation.Yaw, instance_data.TargetRotation.Yaw, 0.01f );
    }

    if ( !instance_data.bUpdateRoll )
    {
        rotation.Roll = current_rotation.Roll;
    }
    else
    {
        rotation_matches &= FMath::IsNearlyEqual( rotation.Roll, instance_data.TargetRotation.Roll, 0.01f );
    }

    instance_data.Actor->SetActorRotation( rotation );

    if ( rotation_matches && instance_data.bFinishTaskWhenRotationIsComplete )
    {
        return EStateTreeRunStatus::Succeeded;
    }

    return EStateTreeRunStatus::Running;
}

void FAIExtStateTreeTaskRotateActor::UpdateTargetRotation( const FStateTreeExecutionContext & context ) const
{
    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.ActorToCopyRotationFrom != nullptr )
    {
        instance_data.TargetRotation = instance_data.ActorToCopyRotationFrom->GetActorRotation();
    }
    else if ( instance_data.ActorToLookAtTo != nullptr )
    {
        instance_data.TargetRotation = UKismetMathLibrary::FindLookAtRotation( instance_data.Actor->GetActorLocation(), instance_data.ActorToLookAtTo->GetActorLocation() );
    }
    else
    {
        instance_data.TargetRotation = instance_data.WorldRotation;
    }
}