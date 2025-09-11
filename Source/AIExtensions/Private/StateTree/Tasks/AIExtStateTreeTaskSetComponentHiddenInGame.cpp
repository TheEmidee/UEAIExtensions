#include "StateTree/Tasks/AIExtStateTreeTaskSetComponentHiddenInGame.h"

#include "StateTreeExecutionContext.h"

FAIExtStateTreeTaskSetComponentHiddenInGame::FAIExtStateTreeTaskSetComponentHiddenInGame()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskSetComponentHiddenInGame::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Component != nullptr )
    {
        instance_data.Component->SetHiddenInGame( instance_data.bHiddenInGame );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}
