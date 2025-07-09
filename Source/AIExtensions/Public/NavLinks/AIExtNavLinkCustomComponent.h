#pragma once

#include <CoreMinimal.h>
#include <NavLinkCustomComponent.h>

#include "AIExtNavLinkCustomComponent.generated.h"

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class AIEXTENSIONS_API UAIExtNavLinkCustomComponent : public UNavLinkCustomComponent
{
    GENERATED_BODY()

public:
    UAIExtNavLinkCustomComponent();

    bool IsLinkPathfindingAllowed( const UObject * querier ) const override;

private:
    const APawn * GetQueriedPawn( const UObject * querier ) const;

    UPROPERTY( EditAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess ) )
    TArray< TSubclassOf< APawn > > AllowedPawnClasses;
};
