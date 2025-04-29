#include "StateTree/Tasks/SmartObjects/AIExtStateTreeTaskSmartObjectFreeSlot.h"

#include <SmartObjectSubsystem.h>
#include <StateTreeExecutionContext.h>
#include <StateTreeLinker.h>
#include <VisualLogger/VisualLogger.h>

FAIExtStateTreeTaskSmartObjectFreeSlot::FAIExtStateTreeTaskSmartObjectFreeSlot()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

bool FAIExtStateTreeTaskSmartObjectFreeSlot::Link( FStateTreeLinker & linker )
{
    linker.LinkExternalData( SmartObjectSubsystemHandle );
    return true;
}

inline EStateTreeRunStatus FAIExtStateTreeTaskSmartObjectFreeSlot::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & smart_object_subsystem = context.GetExternalData( SmartObjectSubsystemHandle );
    const auto & instance_data = context.GetInstanceData( *this );

    if ( !instance_data.ClaimHandle.IsValid() )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskSmartObjectFreeSlot failed because the claim handle is invalid." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( smart_object_subsystem.MarkSlotAsFree( instance_data.ClaimHandle ) )
    {
        return EStateTreeRunStatus::Running;
    }

    UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskSmartObjectFreeSlot failed because an error occured while freeing the claim handle." ) );
    return EStateTreeRunStatus::Failed;
}