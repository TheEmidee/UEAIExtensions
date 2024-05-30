#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ObjectMacros.h"

#include "AIExtTeamEvent.generated.h"

UCLASS()
class AIEXTENSIONS_API UAIExtTeamEvent final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION( BlueprintCallable, Category = "AI|Perception", meta = ( WorldContext = "WorldContextObject" ) )
    static void ReportTeamEvent( UObject * WorldContextObject, AActor * InBroadcaster, AActor * InEnemy, const FVector & InLastKnowLocation, float EventRange, float PassedInfoAge, float InStrength );
};