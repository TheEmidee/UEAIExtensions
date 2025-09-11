#include "StateTree/Conditions/AIExtStateTreeConditionIsSmartObjectSlotHandleValid.h"

#include "SmartObjectSubsystem.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeLinker.h"

bool FAIExtStateTreeConditionIsSmartObjectSlotHandleValid::Link( FStateTreeLinker & linker )
{
    linker.LinkExternalData( SmartObjectSubsystemHandle );
    return true;
}

bool FAIExtStateTreeConditionIsSmartObjectSlotHandleValid::TestCondition( FStateTreeExecutionContext & context ) const
{
    const auto & smart_object_subsystem = context.GetExternalData( SmartObjectSubsystemHandle );
    const auto & instance_data = context.GetInstanceData< FInstanceDataType >( *this );

    return ( instance_data.Slot.IsValid() && smart_object_subsystem.IsSmartObjectSlotValid( instance_data.Slot ) ) ^ bInvert;
}
