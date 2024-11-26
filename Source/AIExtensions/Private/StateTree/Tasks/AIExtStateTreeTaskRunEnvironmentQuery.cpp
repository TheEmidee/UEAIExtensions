#include "StateTree/Tasks/AIExtStateTreeTaskRunEnvironmentQuery.h"

#include <EnvironmentQuery/EnvQuery.h>
#include <EnvironmentQuery/EnvQueryManager.h>
#include <StateTreeExecutionContext.h>
#include <VisualLogger/VisualLogger.h>

void FAIExtStateTreeTaskRunEnvironmentQueryInstanceData::OnQueryFinished( const TSharedPtr< FEnvQueryResult > & env_query_result, FStateTreeExecutionContext & context )
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    if ( !env_query_result->IsSuccessful() )
    {
        RunStatus = EStateTreeRunStatus::Failed;
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery query failed." ) );
        return;
    }

    const auto item_count = env_query_result->Items.Num();
    if ( item_count == 0 )
    {
        RunStatus = EStateTreeRunStatus::Failed;
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery no items returned in the query." ) );
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
        UE_VLOG( context.GetOwner(), LogStateTree, Log, FString::Printf( TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery send state tree event %s." ), *StateTreeEvent.Tag.ToString() ) );
        context.GetMutableEventQueue().SendEvent( ContextOwner, StateTreeEvent.Tag, StateTreeEvent.Payload, StateTreeEvent.Origin );
    }
}

EStateTreeRunStatus FAIExtStateTreeTaskRunEnvironmentQuery::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.Querier == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery failed because the querier is not set." ) );
        return EStateTreeRunStatus::Failed;
    }

    if ( instance_data.QueryTemplate == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery failed because the query template is not set." ) );
        return EStateTreeRunStatus::Failed;
    }

    auto * environment_query_manager = UEnvQueryManager::GetCurrent( instance_data.Querier );

    if ( environment_query_manager == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery failed because there's no environment query manager." ) );
        return EStateTreeRunStatus::Failed;
    }

    FEnvQueryRequest query_request( instance_data.QueryTemplate, instance_data.Querier );
    query_request.SetNamedParams( instance_data.Params );

    instance_data.QueryIndex = environment_query_manager->RunQuery( query_request, instance_data.RunMode, FQueryFinishedSignature::CreateLambda( [ &instance_data, &context ]( TSharedPtr< FEnvQueryResult > env_query_result ) {
        instance_data.OnQueryFinished( env_query_result, context );
    } ) );

    instance_data.RunStatus = EStateTreeRunStatus::Running;
    instance_data.ContextOwner = context.GetOwner();

    UE_VLOG( context.GetOwner(), LogStateTree, Log, FString::Printf( TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery run query %s on %s." ), *GetNameSafe( instance_data.QueryTemplate.Get() ), *GetNameSafe( instance_data.Querier.Get() ) ) );

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAIExtStateTreeTaskRunEnvironmentQuery::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

    auto & instance_data = context.GetInstanceData( *this );
    return instance_data.RunStatus;
}

void FAIExtStateTreeTaskRunEnvironmentQuery::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    TRACE_CPUPROFILER_EVENT_SCOPE_STR( __FUNCTION__ );

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
        UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskRunEnvironmentQuery abort query." ) );
    }
}