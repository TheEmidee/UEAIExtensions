#include "StateTree/Tasks/AIExtStateTreeTaskStopMontage.h"

#include "StateTreeExecutionContext.h"

inline EStateTreeRunStatus FAIExtStateTreeTaskStopMontage::EnterState( FStateTreeExecutionContext & context, const FStateTreeTransitionResult & transition ) const
{
    auto & instance_data = context.GetInstanceData( *this );

    if ( instance_data.SkeletalMeshComponent == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    auto * anim_instance = instance_data.SkeletalMeshComponent->GetAnimInstance();

    if ( anim_instance == nullptr )
    {
        return EStateTreeRunStatus::Failed;
    }

    anim_instance->Montage_Stop( instance_data.BlendOutTime, instance_data.AnimMontage );

    return EStateTreeRunStatus::Running;
}