#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskEnableActorCollision.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskEnableActorCollisionInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskEnableActorCollisionInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Actor = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bCollisionEnabled = true;
};

/**
 * Task to enable/disable actor collisions
 */
USTRUCT( meta = ( DisplayName = "Enable Actor Collisions", Category = "State Tree Tasks|Actor" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskEnableActorCollision : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskEnableActorCollisionInstanceData;

    FAIExtStateTreeTaskEnableActorCollision();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskEnableActorCollision::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}
