#include "StateTree/Tasks/SmartObjects/AIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation.h"

#include <SmartObjectSubsystem.h>
#include <StateTreeExecutionContext.h>
#include <StateTreeLinker.h>
#include <VisualLogger/VisualLogger.h>

FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation::FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation()
{
    // No tick needed.
    bShouldCallTick = false;
    // No need to update bound properties after enter state.
    bShouldCopyBoundPropertiesOnTick = false;
    bShouldCopyBoundPropertiesOnExitState = false;
}

bool FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation::Link( FStateTreeLinker & linker )
{
    linker.LinkExternalData( SmartObjectSubsystemHandle );
    return true;
}

inline EStateTreeRunStatus FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & smart_object_subsystem = context.GetExternalData( SmartObjectSubsystemHandle );
    auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    if ( !instance_data.SlotHandle.IsValid() )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation failed because the slot handle is invalid." ) );
        return EStateTreeRunStatus::Failed;
    }

    const auto transform = smart_object_subsystem.GetSlotTransformChecked( instance_data.SlotHandle );
    instance_data.SlotLocation = transform.GetLocation();
    instance_data.SlotRotationQuat = transform.GetRotation();
    instance_data.SlotRotation = instance_data.SlotRotationQuat.Rotator();

    return EStateTreeRunStatus::Running;
}