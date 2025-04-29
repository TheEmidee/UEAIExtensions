#include "StateTree/Tasks/SmartObjects/AIExtStateTreeTaskSmartObjectSetSlotEnabled.h"

#include <SmartObjectSubsystem.h>
#include <StateTreeExecutionContext.h>
#include <StateTreeLinker.h>
#include <VisualLogger/VisualLogger.h>

FAIExtStateTreeTaskSmartObjectSetSlotEnabled::FAIExtStateTreeTaskSmartObjectSetSlotEnabled()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

bool FAIExtStateTreeTaskSmartObjectSetSlotEnabled::Link( FStateTreeLinker & linker )
{
    linker.LinkExternalData( SmartObjectSubsystemHandle );
    return true;
}

inline EStateTreeRunStatus FAIExtStateTreeTaskSmartObjectSetSlotEnabled::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & smart_object_subsystem = context.GetExternalData( SmartObjectSubsystemHandle );
    const auto & instance_data = context.GetInstanceData( *this );

    if ( !instance_data.SlotHandle.IsValid() )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskSmartObjectSetSlotEnabled failed because the slot handle is invalid." ) );
        return EStateTreeRunStatus::Failed;
    }

    smart_object_subsystem.SetSlotEnabled( instance_data.SlotHandle, instance_data.bEnabled );

    return EStateTreeRunStatus::Running;
}