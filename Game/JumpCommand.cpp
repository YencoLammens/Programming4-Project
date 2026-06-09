#include "JumpCommand.h"
#include "PhysicsComponent.h"
#include "PlayerStateController.h"

dae::JumpCommand::JumpCommand(GameObject* player, PhysicsComponent* physics, PlayerStateController* stateController)
    : GameObjectCommand(player), m_physics(physics), m_stateController(stateController)
{
}

void dae::JumpCommand::Execute(float)
{
    m_physics->Jump();
    m_stateController->OnJump();
}