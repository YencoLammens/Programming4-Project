#pragma once
#include "Command.h"
#include "HealthComponent.h"

namespace dae
{
    class LoseHealthCommand final : public GameObjectCommand
    {
    public:
        LoseHealthCommand(GameObject* gameObject, HealthComponent* healthComponent);
        ~LoseHealthCommand() override = default;

        LoseHealthCommand(const LoseHealthCommand&) = delete;
        LoseHealthCommand& operator=(const LoseHealthCommand&) = delete;
        LoseHealthCommand(LoseHealthCommand&&) = delete;
        LoseHealthCommand& operator=(LoseHealthCommand&&) = delete;

        void Execute(float deltaTime) override;

    private:
        HealthComponent* m_healthComponent;
    };
}