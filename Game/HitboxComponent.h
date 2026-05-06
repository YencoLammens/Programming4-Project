#pragma once
#include "BaseComponent.h"
#include "Rectf.h"

namespace dae
{
    class HitboxComponent final : public BaseComponent
    {
    public:
        HitboxComponent(GameObject* owner, float width, float height);
        ~HitboxComponent() override = default;
        HitboxComponent(const HitboxComponent&) = delete;
        HitboxComponent& operator=(const HitboxComponent&) = delete;
        HitboxComponent(HitboxComponent&&) = delete;
        HitboxComponent& operator=(HitboxComponent&&) = delete;

        void Update(const float) override;
        void FixedUpdate(const float) override {}

        bool Overlaps(const HitboxComponent& other) const;

        float GetWidth()  const { return m_width; }
        float GetHeight() const { return m_height; }
		Rectf GetHitBox() const { return m_hitBox; }

    private:
        float m_width;
        float m_height;
        Rectf m_hitBox;
    };
}