#include "MoveCommand.h"
#include "Transform.h"
#include "FacingComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "PlayerStateController.h"

dae::MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float speed, PlayerStateController* stateController)
    : GameObjectCommand(pGameObject), m_direction(direction), m_speed(speed), m_stateController(stateController), m_render(GetGameObject()->GetComponent<RenderComponent>()), m_facing(GetGameObject()->GetComponent<FacingComponent>()), m_physics(GetGameObject()->GetComponent<PhysicsComponent>()), m_transform(GetGameObject()->GetTransform())
{
}

void dae::MoveCommand::Execute(float deltaTime)
{
    if (m_stateController && m_stateController->IsMovementBlocked())
        return;

    if (m_direction.x != 0.f)
    {
        if (m_facing)
            m_facing->SetFacing(m_direction.x);
        if (m_render)
            m_render->SetFlipX(m_direction.x < 0.f);
        if (m_stateController)
            m_stateController->OnMove();
    }

    if (m_physics)
    {
        m_physics->SetHorizontalVelocity(m_direction.x * m_speed);
        return;
    }

    glm::vec3 pos = m_transform->GetLocalPosition();
    pos += m_direction * m_speed * deltaTime;
    m_transform->SetLocalPosition(pos);
}