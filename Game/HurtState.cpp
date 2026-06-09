#include "HurtState.h"
#include "IdleState.h"
#include "WalkingState.h"
#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "EventId.h"

namespace dae
{
    HurtState::HurtState(float duration)
        : m_duration(duration)
    {
    }

    void HurtState::OnEnter(PlayerStateController* controller)
    {
        m_timer = 0.f;
        if (auto* health = controller->GetHealthComponent())
            health->LoseLife();
        if (auto* anim = controller->GetAnimationComponent())
            anim->Play(make_sdbm_hash("hurt"));
    }

    std::unique_ptr<PlayerCharacterState> HurtState::Update(PlayerStateController* controller, float deltaTime)
    {
        m_timer += deltaTime;
        if (m_timer < m_duration)
            return nullptr;
        if (controller->IsMoving())
            return std::make_unique<WalkingState>();
        return std::make_unique<IdleState>();
    }

    void HurtState::OnExit(PlayerStateController*)
    {
    }
}