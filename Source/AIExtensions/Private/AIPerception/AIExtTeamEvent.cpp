#include "AIPerception/AIExtTeamEvent.h"

#include "Perception/AIPerceptionSystem.h"
#include "Perception/AISense_Team.h"

void UAIExtTeamEvent::ReportTeamEvent( UObject * WorldContextObject, AActor * InBroadcaster, AActor * InEnemy, const FVector & InLastKnowLocation, float EventRange, float PassedInfoAge, float InStrength )
{
    UAIPerceptionSystem * PerceptionSystem = UAIPerceptionSystem::GetCurrent( WorldContextObject );
    if ( PerceptionSystem )
    {
        FAITeamStimulusEvent Event( InBroadcaster, InEnemy, InLastKnowLocation, EventRange, PassedInfoAge, InStrength );
        PerceptionSystem->OnEvent( Event );
    }
}