#include "StateTree/Tasks/AIExtStateTreeTaskEnableAnimation.h"

#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskEnableAnimation::FAIExtStateTreeTaskEnableAnimation()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskEnableAnimation::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.SkeletalMeshComponent != nullptr )
    {
        instance_data.SkeletalMeshComponent->SetAnimationMode( instance_data.AnimationMode );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}