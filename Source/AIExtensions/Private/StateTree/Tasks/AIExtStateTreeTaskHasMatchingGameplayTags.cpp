#include "StateTree/Tasks/AIExtStateTreeTaskHasMatchingGameplayTags.h"

#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskHasMatchingGameplayTags::FAIExtStateTreeTaskHasMatchingGameplayTags()
{
    bShouldCallTick = true;
    bShouldCopyBoundPropertiesOnTick = true;
}

EStateTreeRunStatus FAIExtStateTreeTaskHasMatchingGameplayTags::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    auto result = false;
    switch ( MatchType )
    {
        case EGameplayContainerMatchType::Any:
        {
            result = bExactMatch ? instance_data.TagContainer.HasAnyExact( instance_data.OtherTagContainer ) : instance_data.TagContainer.HasAny( instance_data.OtherTagContainer );
            break;
        }
        case EGameplayContainerMatchType::All:
        {
            result = bExactMatch ? instance_data.TagContainer.HasAllExact( instance_data.OtherTagContainer ) : instance_data.TagContainer.HasAll( instance_data.OtherTagContainer );
            break;
        }
        default:
        {
            checkNoEntry();
        }
    }

    instance_data.bHasTag = result ^ bInvert;

    return EStateTreeRunStatus::Running;
}