#include "StateTree/Tasks/AIExtStateTreeTaskMoveTo.h"

#include <AIController.h>
#include <NavFilters/NavigationQueryFilter.h>
#include <StateTreeExecutionContext.h>
#include <Tasks/AITask_MoveTo.h>

EStateTreeRunStatus FAIExtStateTreeTaskMoveTo::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.AIController == nullptr )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskMoveTo failed since AIController is missing." ) );
        return EStateTreeRunStatus::Failed;
    }

    instance_data.TaskOwner = TScriptInterface< IGameplayTaskOwnerInterface >( instance_data.AIController->FindComponentByInterface( UGameplayTaskOwnerInterface::StaticClass() ) );
    if ( instance_data.TaskOwner == nullptr )
    {
        instance_data.TaskOwner = instance_data.AIController;
    }

    return PerformMoveTask( context, *instance_data.AIController );
}

EStateTreeRunStatus FAIExtStateTreeTaskMoveTo::Tick( FStateTreeExecutionContext & context, const float delta_time ) const
{
    const auto & instance_data = context.GetInstanceData( *this );
    if ( instance_data.MoveToTask != nullptr )
    {
        if ( instance_data.MoveToTask->GetState() == EGameplayTaskState::Finished )
        {
            return instance_data.MoveToTask->WasMoveSuccessful() ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
        }

        if ( instance_data.bTrackMovingGoal && instance_data.TargetActor == nullptr )
        {
            if ( const auto current_destination = instance_data.MoveToTask->GetMoveRequestRef().GetDestination();
                FVector::DistSquared( current_destination, instance_data.Destination ) > ( instance_data.DestinationMoveTolerance * instance_data.DestinationMoveTolerance ) )
            {
                UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskMoveTo destination has moved enough. Restarting task." ) );
                return PerformMoveTask( context, *instance_data.AIController );
            }
        }
        return EStateTreeRunStatus::Running;
    }
    return EStateTreeRunStatus::Failed;
}

void FAIExtStateTreeTaskMoveTo::ExitState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    if ( const auto & instance_data = context.GetInstanceData( *this );
        instance_data.MoveToTask != nullptr && instance_data.MoveToTask->GetState() != EGameplayTaskState::Finished )
    {
        UE_VLOG( context.GetOwner(), LogStateTree, Log, TEXT( "FAIExtStateTreeTaskMoveTo aborting move to because state finished." ) );
        instance_data.MoveToTask->ExternalCancel();
    }
}

UAITask_MoveTo * FAIExtStateTreeTaskMoveTo::PrepareMoveToTask( FStateTreeExecutionContext & context, AAIController & controller, UAITask_MoveTo * existing_task, FAIMoveRequest & move_request ) const
{
    const auto & instance_data = context.GetInstanceData( *this );
    auto * move_task = existing_task != nullptr
                           ? existing_task
                           : UAITask::NewAITask< UAITask_MoveTo >( controller, *instance_data.TaskOwner );

    if ( move_task != nullptr )
    {
        move_task->SetUp( &controller, move_request );
    }

    return move_task;
}

EStateTreeRunStatus FAIExtStateTreeTaskMoveTo::PerformMoveTask( FStateTreeExecutionContext & context, AAIController & controller ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    FAIMoveRequest move_request;
    move_request.SetNavigationFilter( instance_data.FilterClass ? instance_data.FilterClass : controller.GetDefaultNavigationFilterClass() )
        .SetAllowPartialPath( instance_data.bAllowPartialPath )
        .SetAcceptanceRadius( instance_data.AcceptableRadius )
        .SetCanStrafe( instance_data.bAllowStrafe )
        .SetReachTestIncludesAgentRadius( instance_data.bReachTestIncludesAgentRadius )
        .SetReachTestIncludesGoalRadius( instance_data.bReachTestIncludesGoalRadius )
        .SetRequireNavigableEndLocation( instance_data.bRequireNavigableEndLocation )
        .SetProjectGoalLocation( instance_data.bProjectGoalLocation )
        .SetUsePathfinding( true );

    if ( instance_data.TargetActor != nullptr )
    {
        if ( instance_data.bTrackMovingGoal )
        {
            move_request.SetGoalActor( instance_data.TargetActor );
        }
        else
        {
            move_request.SetGoalLocation( instance_data.TargetActor->GetActorLocation() );
        }
    }
    else
    {
        move_request.SetGoalLocation( instance_data.Destination );
    }

    if ( move_request.IsValid() )
    {
        instance_data.MoveToTask = PrepareMoveToTask( context, controller, instance_data.MoveToTask, move_request );
        if ( instance_data.MoveToTask != nullptr )
        {
            if ( instance_data.MoveToTask->IsActive() )
            {
                instance_data.MoveToTask->ConditionalPerformMove();
            }
            else
            {
                instance_data.MoveToTask->ReadyForActivation();
            }

            if ( instance_data.MoveToTask->GetState() == EGameplayTaskState::Finished )
            {
                return instance_data.MoveToTask->WasMoveSuccessful() ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
            }

            return EStateTreeRunStatus::Running;
        }
    }

    UE_VLOG( context.GetOwner(), LogStateTree, Error, TEXT( "FAIExtStateTreeTaskMoveTo failed because it doesn't have a destination." ) );
    return EStateTreeRunStatus::Failed;
}