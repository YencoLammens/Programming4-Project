#include "DeadState.h"
#include "WanderingState.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
    static constexpr float k_respawnX = 200.f;
    static constexpr float k_respawnY = 400.f;

    DeadState::DeadState(float duration)
        : m_duration(duration), m_timer(0.f)
    {
    }

    void DeadState::OnEnter(GameObject* owner)
    {
        m_timer = 0.f;
        owner->GetTransform()->SetLocalPosition(k_respawnX, k_respawnY, 0.f);
    }

    std::unique_ptr<CharacterState> DeadState::HandleInput(GameObject*)
    {
        if (m_timer >= m_duration)
            return std::make_unique<WanderingState>();

        return nullptr;
    }

    void DeadState::Update(GameObject*, float deltaTime)
    {
        m_timer += deltaTime;
    }

    void DeadState::OnExit(GameObject*)
    {
    }
}