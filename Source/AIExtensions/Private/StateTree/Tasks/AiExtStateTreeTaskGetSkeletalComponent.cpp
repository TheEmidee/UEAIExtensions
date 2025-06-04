#include "StateTree/Tasks/AiExtStateTreeTaskGetSkeletalComponent.h"

#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskGetSkeletalMeshComponent::FAIExtStateTreeTaskGetSkeletalMeshComponent()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskGetSkeletalMeshComponent::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Actor != nullptr )
    {
        instance_data.SkeletalMeshComponent = Cast< USkeletalMeshComponent >( instance_data.Actor->GetComponentByClass( USkeletalMeshComponent::StaticClass() ) );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}
