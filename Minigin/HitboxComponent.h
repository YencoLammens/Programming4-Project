#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Rectf.h"
namespace dae
{
    class HitboxComponent final : public BaseComponent, public Subject
    {
    public:
        HitboxComponent(GameObject* owner, float width, float height);
        ~HitboxComponent() override;
        HitboxComponent(const HitboxComponent&) = delete;
        HitboxComponent& operator=(const HitboxComponent&) = delete;
        HitboxComponent(HitboxComponent&&) = delete;
        HitboxComponent& operator=(HitboxComponent&&) = delete;

        void Update(const float) override;
        void FixedUpdate(const float) override {}

        bool Overlaps(const HitboxComponent& other) const;
        void BeginOverlap(HitboxComponent* other);
        void EndOverlap(HitboxComponent* other);
        HitboxComponent* GetOverlapPartner() const { return m_pOverlapPartner; }

        float GetWidth()  const { return m_width; }
        float GetHeight() const { return m_height; }
        Rectf GetHitBox() const { return m_hitBox; }

    private:
        float m_width;
        float m_height;
        Rectf m_hitBox;
        HitboxComponent* m_pOverlapPartner{ nullptr };
    };
}