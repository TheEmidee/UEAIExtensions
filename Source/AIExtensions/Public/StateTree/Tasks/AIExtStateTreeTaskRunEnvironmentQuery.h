#pragma once

#include <AISystem.h>
#include <EnvironmentQuery/EnvQueryTypes.h>
#include <StateTreeEvents.h>
#include <StateTreeTaskBase.h>

#include "AIExtStateTreeTaskRunEnvironmentQuery.generated.h"

class UEnvQuery;

UENUM()
enum class EAIStateTreeTaskRunEnvironmentQueryResultType : uint8
{
    Actor,
    Vector
};

USTRUCT()
struct FAIExtStateTreeTaskRunEnvironmentQueryInstanceData
{
    GENERATED_BODY()

    void OnQueryFinished( const TSharedPtr< FEnvQueryResult > & env_query_result, FStateTreeExecutionContext & context );

    // The querier of the query
    UPROPERTY( EditAnywhere, Category = "Context" )
    TObjectPtr< AActor > Querier = nullptr;

    // The query to execute
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TObjectPtr< UEnvQuery > QueryTemplate = nullptr;

    // The type of result
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TEnumAsByte< EEnvQueryRunMode::Type > RunMode = EEnvQueryRunMode::SingleResult;

    // The type output
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    EAIStateTreeTaskRunEnvironmentQueryResultType Type = EAIStateTreeTaskRunEnvironmentQueryResultType::Vector;

    // The parameters to pass to the query
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    TArray< FEnvNamedValue > Params;

    // Set to true to end the task when the query succeeds
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    bool bFinishTaskOnSuccess;

    // If this is set, then a state tree event will be sent when the query succeeds
    UPROPERTY( EditAnywhere, Category = "Parameter" )
    FStateTreeEvent StateTreeEvent;

    // Will contain the actor found by the query when the run mode is not set to AllMatching
    UPROPERTY( EditAnywhere, Category = "Output" )
    TObjectPtr< AActor > SingleActor;

    // Will contain all the actors that match the query when the run mode is set to AllMatching
    UPROPERTY( EditAnywhere, Category = "Output" )
    TArray< AActor * > AllMatchingActors;

    // Will contain the best location found by the query when the run mode is not set to AllMatching
    UPROPERTY( EditAnywhere, Category = "Output" )
    FVector SingleLocation;

    // Will contain all the locations that match the query when the run mode is set to AllMatching
    UPROPERTY( EditAnywhere, Category = "Output" )
    TArray< FVector > AllMatchingLocations;

    UPROPERTY()
    TObjectPtr< UObject > ContextOwner;

    int QueryIndex;
    EStateTreeRunStatus RunStatus;
};

/**
 * Task to execute an environment query. Can return either one or all the locations or actors
 */
USTRUCT( meta = ( DisplayName = "Run Environment Query", Category = "State Tree Tasks|Environment Query System" ) )
struct AIEXTENSIONS_API FAIExtStateTreeTaskRunEnvironmentQuery : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    FAIExtStateTreeTaskRunEnvironmentQuery() = default;

    using FInstanceDataType = FAIExtStateTreeTaskRunEnvironmentQueryInstanceData;

    const UStruct * GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    }

    EStateTreeRunStatus EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
    EStateTreeRunStatus Tick( FStateTreeExecutionContext & context, const float delta_time ) const override;
    void ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const override;
};