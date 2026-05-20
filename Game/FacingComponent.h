#pragma once
#include "BaseComponent.h"

namespace dae
{
    class FacingComponent final : public BaseComponent
    {
    public:
        explicit FacingComponent(GameObject* owner) : BaseComponent(owner) {}
        ~FacingComponent() override = default;
        FacingComponent(const FacingComponent&) = delete;
        FacingComponent& operator=(const FacingComponent&) = delete;
        FacingComponent(FacingComponent&&) = delete;
        FacingComponent& operator=(FacingComponent&&) = delete;

        void Update(const float) override {}
        void FixedUpdate(const float) override {}

        void SetFacing(float direction) { m_direction = direction > 0.f ? 1.f : -1.f; }
        float GetFacing() const { return m_direction; }

    private:
        float m_direction{ 1.f };
    };
}