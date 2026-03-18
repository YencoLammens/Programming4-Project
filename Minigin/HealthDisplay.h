#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
    class TextComponent;
    class HealthComponent;

    class HealthDisplay final : public BaseComponent, public Observer
    {
    public:
        HealthDisplay(GameObject* owner, Subject* subject, HealthComponent* healthComponent);
        ~HealthDisplay() override = default;

        HealthDisplay(const HealthDisplay&) = delete;
        HealthDisplay& operator=(const HealthDisplay&) = delete;
        HealthDisplay(HealthDisplay&&) = delete;
        HealthDisplay& operator=(HealthDisplay&&) = delete;

        void Update(const float) override {};
        void FixedUpdate(const float) override {};

        void Notify(EventId event) override;

    private:
        TextComponent* m_textComponent{ nullptr };
        HealthComponent* m_healthComponent{ nullptr };
    };
}