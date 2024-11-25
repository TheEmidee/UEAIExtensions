#include "StateTree/Tasks/AIExtStateTreeTaskRunEnvironmentQuery.h"

#include <EnvironmentQuery/EnvQueryManager.h>
#include <StateTreeExecutionContext.h>

void FAIExtStateTreeTaskRunEnvironmentQueryInstanceData::OnQueryFinished( const TSharedPtr< FEnvQueryResult > & env_query_result, FStateTreeEventQueue & event_queue )
{
    if ( !env_query_result->IsSuccessful() )
    {
        RunStatus = EStateTreeRunStatus::Failed;
        return;
    }

    const auto item_count = env_query_result->Items.Num();
    if ( item_count == 0 )
    {
        RunStatus = EStateTreeRunStatus::Failed;
        return;
    }

    if ( bFinishTaskOnSuccess )
    {
        RunStatus = EStateTreeRunStatus::Succeeded;
    }

    switch ( RunMode )
    {
        case EEnvQueryRunMode::SingleResult:
        case EEnvQueryRunMode::RandomBest5Pct:
        case EEnvQueryRunMode::RandomBest25Pct:
        {
            switch ( Type )
            {
                case EAIStateTreeTaskRunEnvironmentQueryResultType::Actor:
                {
                    SingleActor = env_query_result->GetItemAsActor( FMath::RandRange( 0, item_count - 1 ) );
                }
                break;
                case EAIStateTreeTaskRunEnvironmentQueryResultType::Vector:
                {
                    SingleLocation = env_query_result->GetItemAsLocation( FMath::RandRange( 0, item_count - 1 ) );
                }
                break;
                default:
                {
                    checkNoEntry();
                }
                break;
            }
        }
        break;
        case EEnvQueryRunMode::AllMatching:
        {
            switch ( Type )
            {
                case EAIStateTreeTaskRunEnvironmentQueryResultType::Actor:
                {
                    env_query_result->GetAllAsActors( AllMatchingActors );
                }
                break;
                case EAIStateTreeTaskRunEnvironmentQueryResultType::Vector:
                {
                    env_query_result->GetAllAsLocations( AllMatchingLocations );
                }
                break;
                default:
                {
                    checkNoEntry();
                }
                break;
            }
        }
        break;
        default:
        {
            checkNoEntry();
        }
        break;
    }

    if ( StateTreeEvent.Tag.IsValid() )
    {
        event_queue.SendEvent( ContextOwner, StateTreeEvent.Tag, StateTreeEvent.Payload, StateTreeEvent.Origin );
    }
}

EStateTreeRunStatus FAIExtStateTreeTaskRunEnvironmentQuery::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Querier == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.QueryTemplate == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    auto * environment_query_manager = UEnvQueryManager::GetCurrent( instance_data.Querier );

    if ( environment_query_manager == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    FEnvQueryRequest query_request( instance_data.QueryTemplate, instance_data.Querier );
    query_request.SetNamedParams( instance_data.Params );

    FStateTreeEventQueue & event_queue = context.GetMutableEventQueue();

    instance_data.QueryIndex = environment_query_manager->RunQuery( query_request, instance_data.RunMode, FQueryFinishedSignature::CreateLambda( [ &instance_data, &event_queue ]( TSharedPtr< FEnvQueryResult > env_query_result ) {
        instance_data.OnQueryFinished( env_query_result, event_queue );
    } ) );

    instance_data.RunStatus = EStateTreeRunStatus::Running;
    instance_data.ContextOwner = context.GetOwner();

    return FStateTreeTaskCommonBase::EnterState( context, transition );
}

EStateTreeRunStatus FAIExtStateTreeTaskRunEnvironmentQuery::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    auto & instance_data = context.GetInstanceData( *this );
    return instance_data.RunStatus;
}

void FAIExtStateTreeTaskRunEnvironmentQuery::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.QueryIndex == INDEX_NONE )
    {
        return;
    }

    if ( instance_data.Querier == nullptr )
    {
        return;
    }

    if ( auto * environment_query_manager = UEnvQueryManager::GetCurrent( instance_data.Querier ) )
    {
        environment_query_manager->AbortQuery( instance_data.QueryIndex );
    }
}