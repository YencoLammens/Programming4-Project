#pragma once
#include "BaseComponent.h"

namespace dae
{
    class BoulderPoolComponent;
    class FacingComponent;

    class MaitaShootComponent final : public BaseComponent
    {
    public:
        MaitaShootComponent(GameObject* owner, BoulderPoolComponent* boulderPool, FacingComponent* facing);
        ~MaitaShootComponent() override = default;
        MaitaShootComponent(const MaitaShootComponent&) = delete;
        MaitaShootComponent& operator=(const MaitaShootComponent&) = delete;
        MaitaShootComponent(MaitaShootComponent&&) = delete;
        MaitaShootComponent& operator=(MaitaShootComponent&&) = delete;

        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void SetEnabled(bool enabled) { m_enabled = enabled; }

    private:
        BoulderPoolComponent* m_pBoulderPool;
        FacingComponent* m_pFacing;
        float m_shootTimer{ 0.f };
        float m_shootInterval{ 0.f };
        bool m_enabled{ true };

        static constexpr float k_minInterval{ 2.f };
    };
}