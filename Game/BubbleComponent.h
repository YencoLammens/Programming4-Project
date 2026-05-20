#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <glm/glm.hpp>

namespace dae
{
    class HitboxComponent;
    class BubblePoolComponent;
    class Transform;

    class BubbleComponent final : public BaseComponent, public Observer
    {
    public:
        BubbleComponent(GameObject* owner, BubblePoolComponent* pool);
        ~BubbleComponent() override;
        BubbleComponent(const BubbleComponent&) = delete;
        BubbleComponent& operator=(const BubbleComponent&) = delete;
        BubbleComponent(BubbleComponent&&) = delete;
        BubbleComponent& operator=(BubbleComponent&&) = delete;

        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}
        void Notify(EventId event) override;
        void OnSubjectDestroyed() override { m_hitbox = nullptr; }

        void Reset(glm::vec3 position, float direction);
        bool IsActive() const { return m_active; }
        void SetActive(bool active) { m_active = active; }

    private:
        BubblePoolComponent* m_pool;
        HitboxComponent* m_hitbox{ nullptr };
        glm::vec3 m_velocity{};
        float m_travelTimer{ 0.f };
        float m_lifetimeTimer{ 0.f };
        bool m_traveling{ true };
        bool m_active{ false };
        bool m_pendingRelease{ false };

        static constexpr float k_travelDuration{ 1.f };
        static constexpr float k_lifetime{ 8.f };
        static constexpr float k_travelSpeed{ 150.f };
        static constexpr float k_floatSpeed{ 40.f };
        Transform* m_transform{ nullptr };
    };
}