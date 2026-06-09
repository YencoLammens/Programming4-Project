#pragma once
#include "Command.h"

namespace dae
{
    class PlayerStateController;

    class ShootBubbleCommand final : public GameObjectCommand
    {
    public:
        ShootBubbleCommand(GameObject* player, PlayerStateController* stateController);
        ~ShootBubbleCommand() override = default;
        ShootBubbleCommand(const ShootBubbleCommand&) = delete;
        ShootBubbleCommand& operator=(const ShootBubbleCommand&) = delete;
        ShootBubbleCommand(ShootBubbleCommand&&) = delete;
        ShootBubbleCommand& operator=(ShootBubbleCommand&&) = delete;

        void Execute(float) override;

    private:
        PlayerStateController* m_stateController;
    };
}