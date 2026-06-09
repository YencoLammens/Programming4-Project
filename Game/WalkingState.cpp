#include "WalkingState.h"
#include "IdleState.h"
#include "JumpingState.h"
#include "FiringState.h"
#include "HurtState.h"
#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "EventId.h"

namespace dae
{
    void WalkingState::OnEnter(PlayerStateController* controller)
    {
        if (auto* anim = controller->GetAnimationComponent())
            anim->Play(make_sdbm_hash("walk"));
    }

    std::unique_ptr<PlayerCharacterState> WalkingState::Update(PlayerStateController* controller, float)
    {
        if (controller->WasHurtRequested())
            return std::make_unique<HurtState>();
        if (controller->WasJumpRequested())
            return std::make_unique<JumpingState>();
        if (controller->WasShootRequested())
            return std::make_unique<FiringState>();
        if (!controller->IsMoving())
            return std::make_unique<IdleState>();
        return nullptr;
    }

    void WalkingState::OnExit(PlayerStateController*)
    {
    }
}