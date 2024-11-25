#include "StateTree/Tasks/AIExtStateTreeTaskGetActorOwnedTags.h"

#include <GameplayTagAssetInterface.h>
#include <StateTreeExecutionContext.h>

EStateTreeRunStatus FAIExtStateTreeTaskGetActorOwnedTags::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( auto * interface = Cast< IGameplayTagAssetInterface >( instance_data.Actor ) )
    {
        interface->GetOwnedGameplayTags( instance_data.OwnedTags );
    }

    return EStateTreeRunStatus::Running;
}