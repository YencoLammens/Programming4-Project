#include "ShootBubbleCommand.h"
#include "PlayerStateController.h"

namespace dae
{
    ShootBubbleCommand::ShootBubbleCommand(GameObject* player, PlayerStateController* stateController)
        : GameObjectCommand(player), m_stateController(stateController)
    {
    }

    void ShootBubbleCommand::Execute(float)
    {
        m_stateController->OnShoot();
    }
}