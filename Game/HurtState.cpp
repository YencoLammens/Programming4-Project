#include "HurtState.h"
#include "IdleState.h"
#include "WalkingState.h"
#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "EventId.h"
#include "RespawnState.h"
#include "PhysicsComponent.h"

namespace dae
{
    HurtState::HurtState(float duration)
        : m_duration(duration)
    {
    }

    void HurtState::OnEnter(PlayerStateController* controller)
    {
        m_timer = 0.f;
        if (auto* physics = controller->GetPhysicsComponent())
            physics->SetHorizontalVelocity(0.f);
        if (auto* health = controller->GetHealthComponent())
            health->LoseLife();
        if (auto* anim = controller->GetAnimationComponent())
            anim->Play(make_sdbm_hash("hurt"));
    }

    std::unique_ptr<PlayerCharacterState> HurtState::Update(PlayerStateController*, float deltaTime)
    {
        m_timer += deltaTime;
        if (m_timer < m_duration)
            return nullptr;
        return std::make_unique<RespawnState>();
    }

    void HurtState::OnExit(PlayerStateController*)
    {
    }
}