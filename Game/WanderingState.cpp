#include "WanderingState.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
    static constexpr float k_screenLeft = 0.f;
    static constexpr float k_screenRight = 1024.f;

    WanderingState::WanderingState(float speed)
        : m_speed(speed), m_direction(1.f)
    {
    }

    void WanderingState::OnEnter(GameObject*)
    {
        m_direction = 1.f;
    }

    std::unique_ptr<CharacterState> WanderingState::HandleInput(GameObject* owner, float deltaTime)
    {
        auto* transform = owner->GetTransform();
        auto pos = transform->GetWorldPosition();

        pos.x += m_direction * m_speed * deltaTime;

        if (pos.x >= k_screenRight)
        {
            pos.x = k_screenRight;
            m_direction = -1.f;
        }
        else if (pos.x <= k_screenLeft)
        {
            pos.x = k_screenLeft;
            m_direction = 1.f;
        }

        transform->SetLocalPosition(pos);
        return nullptr;
    }

    void WanderingState::OnExit(GameObject*)
    {
    }
}