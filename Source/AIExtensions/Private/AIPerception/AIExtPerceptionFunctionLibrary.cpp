#include "AIPerception/AIExtPerceptionFunctionLibrary.h"

#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Team.h"

void UAIExtPerceptionFunctionLibrary::ReportTeamEvent( UObject * world_context_object, AActor * broadcaster, AActor * enemy, const FVector & last_know_location, float event_range, float passed_info_age, float strength )
{
    if ( auto * perception_system = UAIPerceptionSystem::GetCurrent( world_context_object ) )
    {
        FAITeamStimulusEvent Event( broadcaster, enemy, last_know_location, event_range, passed_info_age, strength );
        perception_system->OnEvent( Event );
    }
}