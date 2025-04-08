#include "StateTree/Tasks/AIExtStateTreeTaskActivateComponent.h"

#include <GameFramework/Actor.h>
#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskActivateComponent::FAIExtStateTreeTaskActivateComponent()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskActivateComponent::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Component == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.bActivate )
    {
        instance_data.Component->Activate( instance_data.bResetOnActivate );
    }
    else
    {
        instance_data.Component->Deactivate();
    }

    return EStateTreeRunStatus::Running;
}