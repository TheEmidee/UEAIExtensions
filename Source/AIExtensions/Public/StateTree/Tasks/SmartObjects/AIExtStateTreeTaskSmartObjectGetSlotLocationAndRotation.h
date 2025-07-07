#pragma once

#include <SmartObjectTypes.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation.generated.h"

struct FStateTreeTransitionResult;
class USmartObjectSubsystem;

USTRUCT()
struct AIEXTENSIONS_API FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotationInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotationInstanceData() = default;

    /** The smart object slot handle */
    UPROPERTY( EditAnywhere, Category = "Context" )
    FSmartObjectSlotHandle SlotHandle;

    /** The slot location */
    UPROPERTY( EditAnywhere, Category = "Output" )
    FVector SlotLocation = FVector::ZeroVector;

    /** The slot location */
    UPROPERTY( EditAnywhere, Category = "Output" )
    FRotator SlotRotation = FRotator::ZeroRotator;

    /** The slot location as a quaternion */
    UPROPERTY( EditAnywhere, Category = "Output" )
    FQuat SlotRotationQuat = FQuat::Identity;
};

/**
 * Task to get the location and rotation of a smart object slot
 */
USTRUCT( meta = ( DisplayName = "Get Slot Location and Rotation", Category = "State Tree Tasks|Smart Objects" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotationInstanceData;

    FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation();

    const UStruct * GetInstanceDataType() const override;
    bool Link( FStateTreeLinker & linker ) override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;

protected:
    /** Handle to retrieve USmartObjectSubsystem. */
    TStateTreeExternalDataHandle< USmartObjectSubsystem > SmartObjectSubsystemHandle;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSmartObjectGetSlotLocationAndRotation::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}