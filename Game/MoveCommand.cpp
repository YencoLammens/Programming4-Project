#include "MoveCommand.h"
#include "Transform.h"
#include "FacingComponent.h"
#include "RenderComponent.h"

dae::MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float speed)
    : GameObjectCommand(pGameObject), m_direction(direction), m_speed(speed)
{
}

void dae::MoveCommand::Execute(float deltaTime)
{
    auto* transform = GetGameObject()->GetTransform();
    glm::vec3 pos = transform->GetLocalPosition();
    pos += m_direction * m_speed * deltaTime;
    transform->SetLocalPosition(pos);

    if (m_direction.x != 0.f)
    {
        auto* facing = GetGameObject()->GetComponent<FacingComponent>();
        if (facing)
            facing->SetFacing(m_direction.x);

        auto* render = GetGameObject()->GetComponent<RenderComponent>();
        if (render)
            render->SetFlipX(m_direction.x < 0.f);
    }
}