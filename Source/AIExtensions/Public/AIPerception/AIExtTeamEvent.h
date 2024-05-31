#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include <UObject/ObjectMacros.h>

#include "AIExtTeamEvent.generated.h"

UCLASS()
class AIEXTENSIONS_API UAIExtTeamEvent final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION( BlueprintCallable, Category = "AI|Perception", meta = ( WorldContext = "WorldContextObject" ) )
    static void ReportTeamEvent( UObject * world_context_object, AActor * in_broadcaster, AActor * in_enemy, const FVector & in_last_know_location, float event_range, float passed_info_age, float in_strength );
};