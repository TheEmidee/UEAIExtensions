#pragma once

#include <SmartObjectTypes.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskSmartObjectSetSlotEnabled.generated.h"

enum class EStateTreeRunStatus : uint8;
struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskSmartObjectSetSlotEnabledInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSmartObjectSetSlotEnabledInstanceData() = default;

    /** The smart object slot handle */
    UPROPERTY( EditAnywhere, Category = "Context" )
    FSmartObjectSlotHandle SlotHandle;

    /** Whether to enable the slot or not */
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bEnabled = false;
};

/**
 * Task to enable a (or not) a smart object slot
 */
USTRUCT( meta = ( DisplayName = "Set Slot Enabled", Category = "State Tree Tasks|Smart Objects" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSmartObjectSetSlotEnabled : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSmartObjectSetSlotEnabledInstanceData;

    FAIExtStateTreeTaskSmartObjectSetSlotEnabled() = default;

    const UStruct * GetInstanceDataType() const override;
    bool Link( FStateTreeLinker & linker ) override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;

protected:
    /** Handle to retrieve USmartObjectSubsystem. */
    TStateTreeExternalDataHandle< USmartObjectSubsystem > SmartObjectSubsystemHandle;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSmartObjectSetSlotEnabled::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}