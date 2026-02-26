#include "RotatorComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include <cmath>

dae::RotatorComponent::RotatorComponent(GameObject* owner, float radius, float speed, glm::vec3 center)
    : BaseComponent(owner), m_radius{ radius }, m_speed{ speed }, m_center {center}
{
}

void dae::RotatorComponent::Update(const float deltaTime)
{
    m_angle += m_speed * deltaTime;

    const float x = m_center.x + std::cos(m_angle) * m_radius;
    const float y = m_center.y + std::sin(m_angle) * m_radius;

    GetOwner()->GetTransform()->SetLocalPosition(x, y, 0.f);
}
