#include "StateTree/Tasks/AIExtStateTreeTaskActorLookAtActor.h"

#include "StateTreeExecutionContext.h"

FAIExtStateTreeTaskActorLookAtActor::FAIExtStateTreeTaskActorLookAtActor()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskActorLookAtActor::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.ActorToRotate != nullptr && instance_data.ActorToLookAt != nullptr )
    {
        instance_data.ActorToRotate->SetActorRotation( ( instance_data.ActorToLookAt->GetActorLocation() - instance_data.ActorToRotate->GetActorLocation() ).Rotation() );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}