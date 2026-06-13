#include "JumpingState.h"
#include "IdleState.h"
#include "WalkingState.h"
#include "HurtState.h"
#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "EventId.h"
#include <iostream>
#include "ServiceLocator.h"

namespace dae
{
    JumpingState::JumpingState(float duration)
        : m_duration(duration)
    {
    }

    void JumpingState::OnEnter(PlayerStateController* controller)
    {
        if (auto* anim = controller->GetAnimationComponent())
            anim->Play(make_sdbm_hash("jump"));
        ServiceLocator::GetSoundSystem().Play(6, 0.1f);
    }

    std::unique_ptr<PlayerCharacterState> JumpingState::Update(PlayerStateController* controller, float deltaTime)
    {
        m_timer += deltaTime;
        if (controller->WasHurtRequested())
            return std::make_unique<HurtState>();
        if (m_timer < m_duration)
            return nullptr;
        if (controller->IsMoving())
            return std::make_unique<WalkingState>();
        return std::make_unique<IdleState>();
    }

    void JumpingState::OnExit(PlayerStateController*)
    {
    }
}