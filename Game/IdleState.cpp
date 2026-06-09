#include "IdleState.h"
#include "WalkingState.h"
#include "JumpingState.h"
#include "FiringState.h"
#include "HurtState.h"
#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "EventId.h"

namespace dae
{
    void IdleState::OnEnter(PlayerStateController* controller)
    {
        if (auto* anim = controller->GetAnimationComponent())
        {
            anim->Play(make_sdbm_hash("idle"));
            anim->Pause();
        }
    }

    std::unique_ptr<PlayerCharacterState> IdleState::Update(PlayerStateController* controller, float)
    {
        if (controller->WasHurtRequested())
            return std::make_unique<HurtState>();
        if (controller->WasJumpRequested())
            return std::make_unique<JumpingState>();
        if (controller->WasShootRequested())
            return std::make_unique<FiringState>();
        if (controller->IsMoving())
            return std::make_unique<WalkingState>();
        return nullptr;
    }

    void IdleState::OnExit(PlayerStateController*)
    {
    }
}