#include "DataProviders/AIExtDataProvider_ScalableFloat.h"

void UAIExtDataProvider_ScalableFloat::BindData( const UObject & owner, int32 request_id )
{
    FloatValue = ScalableFloat.GetValue();

    // int param was encoded directly in the float value
    IntValue = *reinterpret_cast< int32 * >( &FloatValue );

    // bool param was encoded as -1.0f (false) or 1.0f (true) in the float value
    BoolValue = FloatValue > 0.f;
}

FString UAIExtDataProvider_ScalableFloat::ToString( FName prop_name ) const
{
    return FString::Printf( TEXT( "Scalable Float : %s - %s" ), *ScalableFloat.ToSimpleString(), *FString::SanitizeFloat( ScalableFloat.GetValue() ) );
}
