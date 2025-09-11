#pragma once

#include "SmartObjectTypes.h"
#include "StateTreeConditionBase.h"

#include "AIExtStateTreeConditionIsSmartObjectSlotHandleValid.generated.h"

class USmartObjectSubsystem;

USTRUCT()
struct FAIExtStateTreeConditionIsSmartObjectSlotHandleValidInstanceData
{
    GENERATED_BODY()

    UPROPERTY( EditAnywhere, Category = "Input" )
    FSmartObjectSlotHandle Slot;
};

/**
 * Condition to check if a Smart Object slot handle is valid.
 */
USTRUCT( DisplayName = "Is Slot Handle Valid", Category = "Smart Object" )
struct FAIExtStateTreeConditionIsSmartObjectSlotHandleValid : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeConditionIsSmartObjectSlotHandleValidInstanceData;

    FAIExtStateTreeConditionIsSmartObjectSlotHandleValid() = default;

    bool Link( FStateTreeLinker & linker ) override;

    const UStruct * GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }

    bool TestCondition( FStateTreeExecutionContext & context ) const override;

protected:
    UPROPERTY( EditAnywhere, Category = "Condition" )
    bool bInvert = false;

    /** Handle to retrieve USmartObjectSubsystem. */
    TStateTreeExternalDataHandle< USmartObjectSubsystem > SmartObjectSubsystemHandle;
};