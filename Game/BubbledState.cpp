#include "BubbledState.h"
#include "DeadState.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
    BubbledState::BubbledState(float duration)
        : m_duration(duration), m_timer(0.f)
    {
    }

    void BubbledState::OnEnter(GameObject*)
    {
        m_timer = 0.f;
    }

    std::unique_ptr<CharacterState> BubbledState::HandleInput(GameObject*)
    {
        if (m_timer >= m_duration)
            return std::make_unique<DeadState>();

        return nullptr;
    }

    void BubbledState::Update(GameObject* owner, float deltaTime)
    {
        m_timer += deltaTime;

        auto* transform = owner->GetTransform();
        auto pos = transform->GetWorldPosition();
        pos.y -= k_floatSpeed * deltaTime;
        transform->SetLocalPosition(pos);
    }

    void BubbledState::OnExit(GameObject*)
    {
    }
}
