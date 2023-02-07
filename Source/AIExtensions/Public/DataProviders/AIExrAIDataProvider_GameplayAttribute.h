#pragma once

#include <AttributeSet.h>
#include <CoreMinimal.h>
#include <DataProviders/AIDataProvider_QueryParams.h>

#include "AIExrAIDataProvider_GameplayAttribute.generated.h"

UCLASS()
class AIEXTENSIONS_API UAIExrAIDataProvider_GameplayAttribute final : public UAIDataProvider_QueryParams
{
    GENERATED_BODY()

public:
    void BindData( const UObject & owner, int32 request_id ) override;
    FString ToString( FName prop_name ) const override;

protected:
    UPROPERTY( EditAnywhere, Category = "Provider" )
    FGameplayAttribute GameplayAttribute;
};
