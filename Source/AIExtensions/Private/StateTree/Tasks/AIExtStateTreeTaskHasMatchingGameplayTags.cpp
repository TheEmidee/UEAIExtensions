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

    bool bResult = false;
    switch ( MatchType )
    {
        case EGameplayContainerMatchType::Any:
            bResult = bExactMatch ? instance_data.TagContainer.HasAnyExact( instance_data.OtherTagContainer ) : instance_data.TagContainer.HasAny( instance_data.OtherTagContainer );
            break;
        case EGameplayContainerMatchType::All:
            bResult = bExactMatch ? instance_data.TagContainer.HasAllExact( instance_data.OtherTagContainer ) : instance_data.TagContainer.HasAll( instance_data.OtherTagContainer );
            break;
        default:
            ensureMsgf( false, TEXT( "Unhandled match type %s." ), *UEnum::GetValueAsString( MatchType ) );
    }

    instance_data.bHasTag = bResult ^ bInvert;

    return EStateTreeRunStatus::Running;
}