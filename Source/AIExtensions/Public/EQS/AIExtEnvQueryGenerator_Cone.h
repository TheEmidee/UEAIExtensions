#pragma once

#include <CoreMinimal.h>
#include <DataProviders/AIDataProvider.h>
#include <EnvironmentQuery/Generators/EnvQueryGenerator_ProjectedPoints.h>

#include "AIExtEnvQueryGenerator_Cone.generated.h"

UCLASS( meta = ( DisplayName = "Points: Cone", Category = "Generators|AIExt" ) )
class AIEXTENSIONS_API UAIExtEnvQueryGenerator_Cone : public UEnvQueryGenerator_ProjectedPoints
{
    GENERATED_BODY()
public:
    UAIExtEnvQueryGenerator_Cone( const FObjectInitializer & object_initializer = FObjectInitializer::Get() );

    /** Binds data to data providers
     *  @param query_instance - the instance of the query
     */
    void BindDataToDataProviders( const FEnvQueryInstance & query_instance ) const;

    void GenerateItems( FEnvQueryInstance & query_instance ) const override;

    /** Returns the title of the generator on the corresponding node in the EQS Editor window */
    FText GetDescriptionTitle() const override;

    /** Returns the details of the generator on the corresponding node in the EQS Editor window */
    FText GetDescriptionDetails() const override;

protected:
    /** Distance between each point of the same angle */
    UPROPERTY( EditDefaultsOnly, Category = Generator )
    FAIDataProviderFloatValue AlignedPointsDistance;

    /** Maximum degrees of the generated cone */
    UPROPERTY( EditDefaultsOnly, Category = Generator )
    FAIDataProviderFloatValue ConeDegrees;

    /** The step of the angle increase. Angle step must be >=1
     *  Smaller values generate less items
     */
    UPROPERTY( EditDefaultsOnly, Category = Generator )
    FAIDataProviderFloatValue AngleStep;

    /** Minimum generation distance */
    UPROPERTY( EditDefaultsOnly, Category = Generator )
    FAIDataProviderFloatValue MinRange;

    /** Maximum generation distance */
    UPROPERTY( EditDefaultsOnly, Category = Generator )
    FAIDataProviderFloatValue MaxRange;

    /** The actor (or actors) around which the cone will be generated */
    UPROPERTY( EditAnywhere, Category = Generator )
    TSubclassOf< UEnvQueryContext > CenterContext;

    /** The rotation to use for the cone */
    UPROPERTY( EditAnywhere, Category = Generator )
    FEnvDirection RotationDirection;

    /** Offsets the rotation by rotating around the z-axis */
    UPROPERTY( EditAnywhere, Category = Generator )
    FAIDataProviderFloatValue RotationOffset;

    /** Whether to include CenterActors' locations when generating items.
     *	Note that this option skips the MinAngledPointsDistance parameter. */
    UPROPERTY( EditAnywhere, Category = Generator )
    uint8 bIncludeContextLocation : 1;

private:
    FVector GetDirection( FEnvQueryInstance & query_instance ) const;
};