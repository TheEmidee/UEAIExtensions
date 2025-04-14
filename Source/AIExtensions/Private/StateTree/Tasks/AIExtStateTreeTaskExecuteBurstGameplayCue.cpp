#include "StateTree/Tasks/AIExtStateTreeTaskExecuteBurstGameplayCue.h"

#include <GameplayCueFunctionLibrary.h>
#include <StateTreeExecutionContext.h>

FAIExtStateTreeTaskExecuteBurstGameplayCue::FAIExtStateTreeTaskExecuteBurstGameplayCue()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

EStateTreeRunStatus FAIExtStateTreeTaskExecuteBurstGameplayCue::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( instance_data.Actor != nullptr && instance_data.GameplayCueTag.GetTagName() != NAME_None )
    {
        UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor( instance_data.Actor, instance_data.GameplayCueTag, instance_data.Parameters );

        return EStateTreeRunStatus::Running;
    }

    return EStateTreeRunStatus::Failed;
}
