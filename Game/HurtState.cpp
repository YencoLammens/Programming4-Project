#include "HurtState.h"
#include "IdleState.h"
#include "HealthComponent.h"
#include "GameObject.h"

namespace dae
{
    HurtState::HurtState(float duration)
        : m_duration(duration)
    {
    }

    void HurtState::OnEnter(GameObject* owner)
    {
        m_timer = 0.f;
        owner->GetComponent<HealthComponent>()->LoseLife();
    }

    std::unique_ptr<CharacterState> HurtState::HandleInput(GameObject*, float deltaTime)
    {
        m_timer += deltaTime;
        if (m_timer >= m_duration)
            return std::make_unique<IdleState>();
        return nullptr;
    }

    void HurtState::OnExit(GameObject*)
    {
    }
}