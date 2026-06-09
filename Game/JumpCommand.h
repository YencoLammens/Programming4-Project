#pragma once
#include "Command.h"

namespace dae
{
    class PlayerStateController;
    class PhysicsComponent;

    class JumpCommand final : public GameObjectCommand
    {
    public:
        JumpCommand(GameObject* player, PhysicsComponent* physics, PlayerStateController* stateController);
        void Execute(float) override;

    private:
        PhysicsComponent* m_physics;
		PlayerStateController* m_stateController;
    };
}