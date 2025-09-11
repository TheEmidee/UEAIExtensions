#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ObjectMacros.h"

#include "AIExtPerceptionFunctionLibrary.generated.h"

UCLASS()
class AIEXTENSIONS_API UAIExtPerceptionFunctionLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION( BlueprintCallable, Category = "AI|Perception", meta = ( WorldContext = "world_context_object" ) )
    static void ReportTeamEvent( UObject * world_context_object, AActor * broadcaster, AActor * enemy, const FVector & last_know_location, float event_range, float passed_info_age, float strength );
};