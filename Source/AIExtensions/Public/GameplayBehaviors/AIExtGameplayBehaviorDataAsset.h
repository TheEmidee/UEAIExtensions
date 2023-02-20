#pragma once

#include <CoreMinimal.h>
#include <Engine/DataAsset.h>

#include "AIExtGameplayBehaviorDataAsset.generated.h"

class UGameplayBehaviorConfig;

UCLASS()
class AIEXTENSIONS_API UAIExtGameplayBehaviorDataAsset final : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY( EditAnywhere, BlueprintReadOnly, Instanced )
    TObjectPtr< UGameplayBehaviorConfig > GameplayBehaviorConfig;
};
