#pragma once
#include "BaseComponent.h"

namespace dae
{
    class HitboxComponent;
    class Transform;

    class PhysicsComponent final : public BaseComponent
    {
    public:
        explicit PhysicsComponent(GameObject* owner);
        ~PhysicsComponent() override = default;
        PhysicsComponent(const PhysicsComponent&) = delete;
        PhysicsComponent& operator=(const PhysicsComponent&) = delete;
        PhysicsComponent(PhysicsComponent&&) = delete;
        PhysicsComponent& operator=(PhysicsComponent&&) = delete;

        void Update(const float) override {}
        void FixedUpdate(const float fixedTimeStep) override;

        void Jump();
		const float GetHorizontalVelocity() { return m_velocityX; }
        void SetHorizontalVelocity(float vx) { m_velocityX = vx; }
        void ResetVelocity() { m_velocityX = 0.f; m_velocityY = 0.f; }
        bool IsGrounded() const { return m_isGrounded; }
        void SetEnabled(bool enabled) { m_enabled = enabled; }
        bool IsEnabled() const { return m_enabled; }

    private:
        void ResolvePlatforms(float prevBottom, Transform* transform);
        void ResolveWalls(Transform* transform);
        void ResolveBubbles(Transform* transform);

        static constexpr float k_gravity = 350.f;
        static constexpr float k_jumpSpeed = 250.f;
        static constexpr float k_maxFallSpeed = 200.f;

        float m_velocityX{ 0.f };
        float m_velocityY{ 0.f };
        bool m_isGrounded{ false };
        bool m_enabled{ true };
        HitboxComponent* m_hitbox{ nullptr };
    };
}