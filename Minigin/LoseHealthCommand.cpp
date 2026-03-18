#include "LoseHealthCommand.h"

namespace dae
{
    LoseHealthCommand::LoseHealthCommand(GameObject* gameObject, HealthComponent* healthComponent)
        : GameObjectCommand(gameObject), m_healthComponent(healthComponent)
    {
    }

    void LoseHealthCommand::Execute(float)
    {
        m_healthComponent->LoseLife();
    }
}