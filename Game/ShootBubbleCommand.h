#pragma once
#include "Command.h"

namespace dae
{
    class BubblePoolComponent;
    class FacingComponent;

    class ShootBubbleCommand final : public GameObjectCommand
    {
    public:
        ShootBubbleCommand(GameObject* player, BubblePoolComponent* pool);
        ~ShootBubbleCommand() override = default;
        ShootBubbleCommand(const ShootBubbleCommand&) = delete;
        ShootBubbleCommand& operator=(const ShootBubbleCommand&) = delete;
        ShootBubbleCommand(ShootBubbleCommand&&) = delete;
        ShootBubbleCommand& operator=(ShootBubbleCommand&&) = delete;

        void Execute(float deltaTime) override;

    private:
        BubblePoolComponent* m_pool;
        FacingComponent* m_facing;
    };
}