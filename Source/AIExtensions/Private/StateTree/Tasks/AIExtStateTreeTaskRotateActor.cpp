#include "StateTree/Tasks/AIExtStateTreeTaskRotateActor.h"

#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskRotateActor::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.ActorToRotate == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskApplyGameplayEffect can't apply gameplay effect because no ability system was bound." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.ActorToCopyRotationFrom != nullptr )
    {
        instance_data.TargetRotation = instance_data.ActorToCopyRotationFrom->GetActorRotation();
    }
    else
    {
        instance_data.TargetRotation = instance_data.WorldRotation;
    }

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAIExtStateTreeTaskRotateActor::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    const auto current_rotation = instance_data.ActorToRotate->GetActorRotation();

    if ( current_rotation.Equals( instance_data.TargetRotation, 0.01f ) )
    {
        if ( instance_data.bFinishTaskWhenRotationIsComplete )
        {
            return EStateTreeRunStatus::Succeeded;
        }
    }

    const auto rotation = FMath::RInterpConstantTo( current_rotation, instance_data.TargetRotation, delta_time, instance_data.RotationSpeed );
    instance_data.ActorToRotate->SetActorRotation( rotation );

    return EStateTreeRunStatus::Running;
}