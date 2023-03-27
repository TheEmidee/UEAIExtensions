#include "EQS/AIExtEnvQueryGenerator_Cone.h"

#include <EnvironmentQuery/Contexts/EnvQueryContext_Item.h>
#include <EnvironmentQuery/Contexts/EnvQueryContext_Querier.h>

#define LOCTEXT_NAMESPACE "EnvQueryGenerator"

UAIExtEnvQueryGenerator_Cone::UAIExtEnvQueryGenerator_Cone( const FObjectInitializer & object_initializer ) :
    Super( object_initializer )
{
    CenterContext = UEnvQueryContext_Querier::StaticClass();
    AlignedPointsDistance.DefaultValue = 100.f;
    ConeDegrees.DefaultValue = 90.f;
    AngleStep.DefaultValue = 10.f;
    MinRange.DefaultValue = 0.0f;
    MaxRange.DefaultValue = 1000.f;
    CenterContext = UEnvQueryContext_Querier::StaticClass();
    RotationDirection.DirMode = EEnvDirection::Rotation;
    RotationDirection.Rotation = UEnvQueryContext_Querier::StaticClass();
    RotationOffset.DefaultValue = 0.0f;
    bIncludeContextLocation = false;
}

void UAIExtEnvQueryGenerator_Cone::BindDataToDataProviders( const FEnvQueryInstance & query_instance ) const
{
    // Bind the necessary data to data providers
    const auto * bind_owner = query_instance.Owner.Get();
    AlignedPointsDistance.BindData( bind_owner, query_instance.QueryID );
    ConeDegrees.BindData( bind_owner, query_instance.QueryID );
    AngleStep.BindData( bind_owner, query_instance.QueryID );
    MinRange.BindData( bind_owner, query_instance.QueryID );
    MaxRange.BindData( bind_owner, query_instance.QueryID );
    RotationOffset.BindData( bind_owner, query_instance.QueryID );
}

void UAIExtEnvQueryGenerator_Cone::GenerateItems( FEnvQueryInstance & query_instance ) const
{
    TArray< FVector > center_locations;
    query_instance.PrepareContext( CenterContext, center_locations );

    BindDataToDataProviders( query_instance );

    const auto cone_degrees_value = FMath::Clamp( FMath::Abs( ConeDegrees.GetValue() ), 0.f, 359.f );
    if ( cone_degrees_value == 0 )
    {
        return;
    }

    // Get the values from each data provider
    const auto aligned_point_distance_value = AlignedPointsDistance.GetValue();
    const auto angle_step_value = FMath::Clamp( AngleStep.GetValue(), 1.f, 359.f );
    const auto min_generation_range = FMath::Clamp( MinRange.GetValue(), 0.f, MaxRange.GetValue() );
    const auto max_generation_range = FMath::Clamp( MaxRange.GetValue(), MinRange.GetValue(), MAX_flt );
    const auto max_points_per_angle_value = FMath::FloorToInt( ( max_generation_range - min_generation_range ) / aligned_point_distance_value );

    TArray< FNavLocation > generated_items;
    generated_items.Reserve( center_locations.Num() * FMath::CeilToInt( cone_degrees_value / angle_step_value ) * max_points_per_angle_value + 1 );

    // Generate points for each actor
    for ( auto center_index = 0; center_index < center_locations.Num(); center_index++ )
    {
        TArray< FRotator > rotations;
        query_instance.PrepareContext( RotationDirection.Rotation, rotations );

        const auto forward_vector = GetDirection( query_instance ).RotateAngleAxis( RotationOffset.GetValue(), FVector::UpVector );
        const auto actor_location = center_locations[ center_index ];

        for ( auto angle = -( cone_degrees_value * 0.5f ); angle <= ( cone_degrees_value * 0.5f ); angle += angle_step_value )
        {
            const auto axis_direction = forward_vector.RotateAngleAxis( angle, FVector::UpVector );

            // skipping PointIndex == 0 as that's the context's location
            for ( auto point_index = 1; point_index <= max_points_per_angle_value; point_index++ )
            {
                const auto generated_location = actor_location + ( axis_direction * ( min_generation_range + point_index * aligned_point_distance_value ) );
                generated_items.Add( FNavLocation( generated_location ) );
            }
        }

        if ( bIncludeContextLocation )
        {
            generated_items.Add( FNavLocation( actor_location ) );
        }
    }

    ProjectAndFilterNavPoints( generated_items, query_instance );
    StoreNavPoints( generated_items, query_instance );
}

FText UAIExtEnvQueryGenerator_Cone::GetDescriptionTitle() const
{
    return FText::Format( LOCTEXT( "AIExtConeDescriptionGenerateAroundContext", "{0}: generate in front of {1}" ),
        Super::GetDescriptionTitle(),
        UEnvQueryTypes::DescribeContext( CenterContext ) );
}

FText UAIExtEnvQueryGenerator_Cone::GetDescriptionDetails() const
{
    auto desc = FText::Format( LOCTEXT( "AIExtConeDescription", "degrees: {0}, angle step: {1}" ),
        FText::FromString( ConeDegrees.ToString() ),
        FText::FromString( AngleStep.ToString() ) );

    const auto proj_desc = ProjectionData.ToText( FEnvTraceData::Brief );
    if ( !proj_desc.IsEmpty() )
    {
        FFormatNamedArguments proj_args;
        proj_args.Add( TEXT( "AIExtDescription" ), desc );
        proj_args.Add( TEXT( "AIExtProjectionDescription" ), proj_desc );
        desc = FText::Format( LOCTEXT( "AIExtConeDescriptionWithProjection", "{AIExtDescription}, {AIExtProjectionDescription}" ), proj_args );
    }

    return desc;
}

FVector UAIExtEnvQueryGenerator_Cone::GetDirection( FEnvQueryInstance & query_instance ) const
{
    switch ( RotationDirection.DirMode )
    {
        case EEnvDirection::Rotation:
        {
            TArray< FRotator > rotations;
            query_instance.PrepareContext( RotationDirection.Rotation, rotations );
            if ( rotations.IsEmpty() )
            {
                return FVector();
            }

            auto result = rotations[ 0 ].Vector();
            result.Normalize();
            return result;
        }
        case EEnvDirection::TwoPoints:
        {
            TArray< FVector > source_locations;
            TArray< FVector > target_locations;

            query_instance.PrepareContext( RotationDirection.LineFrom, source_locations );
            query_instance.PrepareContext( RotationDirection.LineTo, target_locations );
            if ( source_locations.IsEmpty() || target_locations.IsEmpty() )
            {
                return FVector();
            }

            auto result = target_locations[ 0 ] - source_locations[ 0 ];
            result.Normalize();
            return result;
        }
        default:
        {
            checkNoEntry();
            return FVector();
        };
    }
}