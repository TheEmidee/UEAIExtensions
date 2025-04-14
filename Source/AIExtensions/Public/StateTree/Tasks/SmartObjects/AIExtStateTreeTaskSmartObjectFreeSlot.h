#pragma once

#include <SmartObjectRuntime.h>
#include <SmartObjectTypes.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskSmartObjectFreeSlot.generated.h"

struct FStateTreeTransitionResult;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskSmartObjectFreeSlotInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSmartObjectFreeSlotInstanceData() = default;

    /** The smart object slot handle */
    UPROPERTY( EditAnywhere, Category = "Context" )
    FSmartObjectClaimHandle ClaimHandle;
};

/**
 * Task to free a claimed smart object slot
 */
USTRUCT( meta = ( DisplayName = "Free Slot", Category = "State Tree Tasks|Smart Objects" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSmartObjectFreeSlot : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSmartObjectFreeSlotInstanceData;

    FAIExtStateTreeTaskSmartObjectFreeSlot();

    const UStruct * GetInstanceDataType() const override;
    bool Link( FStateTreeLinker & linker ) override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;

protected:
    /** Handle to retrieve USmartObjectSubsystem. */
    TStateTreeExternalDataHandle< USmartObjectSubsystem > SmartObjectSubsystemHandle;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSmartObjectFreeSlot::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}