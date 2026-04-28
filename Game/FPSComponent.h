#pragma once
#include "BaseComponent.h"

namespace dae
{
    class TextComponent;

    class FPSComponent final : public BaseComponent
    {
    public:
        explicit FPSComponent(GameObject* owner);
        virtual ~FPSComponent() override = default;

        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

        void Update(const float deltaTime) override;
        void FixedUpdate(const float) override {};

    private:
        TextComponent* m_pTextComponent;
        float m_accumulatedTime;
        int m_frameCount;
        float m_updateInterval;
    };
}
