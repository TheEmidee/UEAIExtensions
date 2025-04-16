#pragma once

#include <CoreMinimal.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskSetComponentHiddenInGame.generated.h"

USTRUCT()
struct FAIExtStateTreeTaskSetComponentHiddenInGameInstanceData
{
    GENERATED_BODY()

    FAIExtStateTreeTaskSetComponentHiddenInGameInstanceData() = default;

    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< UPrimitiveComponent > Component = nullptr;

    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bHiddenInGame = false;
};

/**
 * Task to set PrimitiveComponent Hidden in game
 */
USTRUCT( meta = ( DisplayName = "Set Component Hidden In Game", Category = "State Tree Tasks|Primitive Component" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskSetComponentHiddenInGame : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FAIExtStateTreeTaskSetComponentHiddenInGameInstanceData;

    FAIExtStateTreeTaskSetComponentHiddenInGame();

    const UStruct * GetInstanceDataType() const override;

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};

FORCEINLINE const UStruct * FAIExtStateTreeTaskSetComponentHiddenInGame::GetInstanceDataType() const
{
    return FInstanceDataType::StaticStruct();
}