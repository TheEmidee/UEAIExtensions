#include "NavLinks/AIExtNavLinkCustomComponent.h"

UAIExtNavLinkCustomComponent::UAIExtNavLinkCustomComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

bool UAIExtNavLinkCustomComponent::IsLinkPathfindingAllowed( const UObject * querier ) const
{
    if ( const auto * pawn = GetQueriedPawn( querier ) )
    {
        return AllowedPawnClasses.Contains( pawn->GetClass() );
    }

    return false;
}

const APawn * UAIExtNavLinkCustomComponent::GetQueriedPawn( const UObject * querier ) const
{
    if ( const auto * pawn = Cast< APawn >( querier ) )
    {
        return pawn;
    }

    if ( const auto * controller = Cast< AController >( querier ) )
    {
        return controller->GetPawn();
    }

    return nullptr;
}