#include "RespawnState.h"
#include "IdleState.h"
#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "EventId.h"

namespace dae
{
    RespawnState::RespawnState(float duration, float invincibilityDuration)
        : m_duration(duration), m_invincibilityDuration(invincibilityDuration)
    {
    }

    void RespawnState::OnEnter(PlayerStateController* controller)
    {
        m_timer = 0.f;
        controller->Respawn();
        controller->SetInvincible(m_invincibilityDuration);
        if (auto* anim = controller->GetAnimationComponent())
            anim->Play(make_sdbm_hash("idle"));
    }

    std::unique_ptr<PlayerCharacterState> RespawnState::Update(PlayerStateController*, float deltaTime)
    {
        m_timer += deltaTime;
        if (m_timer < m_duration)
            return nullptr;
        return std::make_unique<IdleState>();
    }

    void RespawnState::OnExit(PlayerStateController*)
    {
    }
}