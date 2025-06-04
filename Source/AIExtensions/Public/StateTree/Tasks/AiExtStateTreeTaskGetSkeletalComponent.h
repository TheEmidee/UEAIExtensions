#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AiExtStateTreeTaskGetSkeletalComponent.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskGetSkeletalMeshComponentInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskGetSkeletalMeshComponentInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor;

    UPROPERTY( EditAnywhere, Category = "Output" )
    TObjectPtr< USkeletalMeshComponent > SkeletalMeshComponent = nullptr;
};

/**
 * Task to get SkeletalMeshComponent of an actor
 */

USTRUCT( meta = ( DisplayName = "Get Skeletal Mesh Component", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskGetSkeletalMeshComponent final : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()
    using FInstanceDataType = FAIExtStateTreeTaskGetSkeletalMeshComponentInstanceData;

    FAIExtStateTreeTaskGetSkeletalMeshComponent();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskGetSkeletalMeshComponent::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
