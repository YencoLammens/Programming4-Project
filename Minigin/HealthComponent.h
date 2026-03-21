#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
    class HealthComponent final : public BaseComponent, public Subject
    {
    public:
        explicit HealthComponent(GameObject* owner, int lives = 3);
        ~HealthComponent() override = default;

        HealthComponent(const HealthComponent&) = delete;
        HealthComponent& operator=(const HealthComponent&) = delete;
        HealthComponent(HealthComponent&&) = delete;
        HealthComponent& operator=(HealthComponent&&) = delete;

        void Update(const float) override {}
        void FixedUpdate(const float) override {}

        void LoseLife();
        int GetLives() const { return m_lives; }

    private:
        int m_lives;
    };
}