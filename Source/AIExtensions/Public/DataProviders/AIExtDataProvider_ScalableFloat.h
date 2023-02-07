#pragma once

#include <CoreMinimal.h>
#include <DataProviders/AIDataProvider_QueryParams.h>
#include <ScalableFloat.h>

#include "AIExtDataProvider_ScalableFloat.generated.h"

UCLASS()
class AIEXTENSIONS_API UAIExtDataProvider_ScalableFloat final : public UAIDataProvider_QueryParams
{
    GENERATED_BODY()

public:
    void BindData( const UObject & owner, int32 request_id ) override;
    FString ToString( FName prop_name ) const override;

protected:
    UPROPERTY( EditAnywhere, Category = "Provider" )
    FScalableFloat ScalableFloat;
};
