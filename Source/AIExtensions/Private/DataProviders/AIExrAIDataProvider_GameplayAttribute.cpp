#include "DataProviders/AIExrAIDataProvider_GameplayAttribute.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAIExrAIDataProvider_GameplayAttribute::BindData( const UObject & owner, int32 request_id )
{
    if ( const auto * asc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent( const_cast < AActor * >( Cast< AActor >( &owner ) ) ) )
    {
        FloatValue = asc->GetNumericAttribute( GameplayAttribute );

        // int param was encoded directly in the float value
        IntValue = *( ( int32 * ) &FloatValue );

        // bool param was encoded as -1.0f (false) or 1.0f (true) in the float value
        BoolValue = FloatValue > 0.f;
    }
    else
    {
        IntValue = 0;
        FloatValue = 0.0f;
        BoolValue = false;
    }
}

FString UAIExrAIDataProvider_GameplayAttribute::ToString( FName prop_name ) const
{
    return FString::Printf( TEXT( "Gameplay Attribute : %s" ), *GameplayAttribute.GetName() );
}
