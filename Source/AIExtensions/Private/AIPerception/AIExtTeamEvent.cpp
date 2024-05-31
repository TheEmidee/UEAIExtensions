#include "AIPerception/AIExtTeamEvent.h"

#include <Perception/AIPerceptionSystem.h>
#include <Perception/AISense_Team.h>

void UAIExtTeamEvent::ReportTeamEvent( UObject * world_context_object, AActor * in_broadcaster, AActor * in_enemy, const FVector & in_last_know_location, float event_range, float passed_info_age, float in_strength )
{
    if ( auto * perception_system = UAIPerceptionSystem::GetCurrent( world_context_object ) )
    {
        FAITeamStimulusEvent Event( in_broadcaster, in_enemy, in_last_know_location, event_range, passed_info_age, in_strength );
        perception_system->OnEvent( Event );
    }
}