#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <glm/glm.hpp>

namespace dae
{
    class HitboxComponent;
    class BoulderPoolComponent;
    class PhysicsComponent;
    class Transform;
    class AnimationComponent;

    class BoulderComponent final : public BaseComponent, public Observer
    {
    public:
        BoulderComponent(GameObject* owner, BoulderPoolComponent* pool);
        ~BoulderComponent() override;
        BoulderComponent(const BoulderComponent&) = delete;
        BoulderComponent& operator=(const BoulderComponent&) = delete;
        BoulderComponent(BoulderComponent&&) = delete;
        BoulderComponent& operator=(BoulderComponent&&) = delete;

        void Update(float deltaTime) override;
        void FixedUpdate(float fixedTimeStep) override;
        void Notify(EventId event) override;
        void OnSubjectDestroyed() override { m_hitbox = nullptr; }

        void Reset(glm::vec3 position, float direction);
        bool IsActive() const { return m_active; }
        void SetActive(bool active) { m_active = active; }

    private:
        BoulderPoolComponent* m_pool;
        HitboxComponent* m_hitbox{ nullptr };
        PhysicsComponent* m_physics{ nullptr };
        Transform* m_transform{ nullptr };
        AnimationComponent* m_animation{ nullptr };

        float m_direction{ 1.f };
        float m_lifetimeTimer{ 0.f };
        bool m_active{ false };
        bool m_pendingRelease{ false };

        static constexpr float k_lifetime{ 8.f };
        static constexpr float k_speed{ 120.f };
        static constexpr float k_wallMargin{ 2.f };
    };
}