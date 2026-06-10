#pragma once
#include <memory>
#include "BaseComponent.h"
#include "PlayerCharacterState.h"
#include <glm/glm.hpp>

namespace dae
{
    class AnimationComponent;
    class PhysicsComponent;
    class FacingComponent;
    class HealthComponent;
    class BubblePoolComponent;

    class PlayerStateController final : public BaseComponent
    {
    public:
        PlayerStateController(GameObject* owner, std::unique_ptr<PlayerCharacterState> initialState, BubblePoolComponent* bubblePool);
        ~PlayerStateController() override = default;
        PlayerStateController(const PlayerStateController&) = delete;
        PlayerStateController& operator=(const PlayerStateController&) = delete;
        PlayerStateController(PlayerStateController&&) = delete;
        PlayerStateController& operator=(PlayerStateController&&) = delete;

        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void OnJump();
        void OnShoot();
        void OnHurt();
        void OnMove();

        bool IsMoving() const;
        bool WasJumpRequested() const { return m_jumpRequested; }
        bool WasShootRequested() const { return m_shootRequested; }
        bool WasHurtRequested() const { return m_hurtRequested; }
        bool IsMovementBlocked() const;
        bool IsInvincible() const;

        void SetInvincible(float duration);
        void SetSpawnPosition(const glm::vec3& pos);
        void Respawn();

        AnimationComponent* GetAnimationComponent() const { return m_animation; }
        PhysicsComponent* GetPhysicsComponent() const { return m_physics; }
        FacingComponent* GetFacingComponent() const { return m_facing; }
        HealthComponent* GetHealthComponent() const { return m_health; }
        BubblePoolComponent* GetBubblePool() const { return m_bubblePool; }

        void SetState(std::unique_ptr<PlayerCharacterState> newState);

    private:
        std::unique_ptr<PlayerCharacterState> m_currentState;

        AnimationComponent* m_animation{ nullptr };
        PhysicsComponent* m_physics{ nullptr };
        FacingComponent* m_facing{ nullptr };
        HealthComponent* m_health{ nullptr };
        BubblePoolComponent* m_bubblePool{ nullptr };

        glm::vec3 m_spawnPosition{};
        float m_invincibilityTimer{ 0.f };
        bool m_jumpRequested{ false };
        bool m_shootRequested{ false };
        bool m_hurtRequested{ false };
        bool m_moveRequested{ false };
        
    };
}