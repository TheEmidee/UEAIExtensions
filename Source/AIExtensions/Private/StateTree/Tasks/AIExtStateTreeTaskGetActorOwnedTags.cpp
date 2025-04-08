#include "StateTree/Tasks/AIExtStateTreeTaskGetActorOwnedTags.h"

#include <GameplayTagAssetInterface.h>
#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskGetActorOwnedTags::FAIExtStateTreeTaskGetActorOwnedTags()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskGetActorOwnedTags::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( auto * interface = Cast< IGameplayTagAssetInterface >( instance_data.Actor ) )
    {
        interface->GetOwnedGameplayTags( instance_data.OwnedTags );
    }

    return EStateTreeRunStatus::Running;
}