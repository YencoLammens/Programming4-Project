#pragma once
#include <memory>
#include "BaseComponent.h"
#include "IEnemyStateController.h"
#include "EnemyCharacterState.h"

namespace dae
{
    class HitboxComponent;
    class PhysicsComponent;
    class FacingComponent;
    class RenderComponent;
    class AnimationComponent;
    class FoodPoolComponent;
    class MaitaShootComponent;

    class MaitaStateController final : public BaseComponent, public IEnemyStateController
    {
    public:
        MaitaStateController(GameObject* owner, std::unique_ptr<EnemyCharacterState> initialState, FoodPoolComponent* foodPool, MaitaShootComponent* shoot);
        ~MaitaStateController() override = default;
        MaitaStateController(const MaitaStateController&) = delete;
        MaitaStateController& operator=(const MaitaStateController&) = delete;
        MaitaStateController(MaitaStateController&&) = delete;
        MaitaStateController& operator=(MaitaStateController&&) = delete;

        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void OnBubbled() override;
        void OnPopped() override;

        HitboxComponent* GetHitboxComponent() const override { return m_hitbox; }
        PhysicsComponent* GetPhysicsComponent() const override { return m_physics; }
        FacingComponent* GetFacingComponent() const override { return m_facing; }
        RenderComponent* GetRenderComponent() const override { return m_render; }
        AnimationComponent* GetAnimationComponent() const override { return m_animation; }
		GameObject* GetOwner() const override { return BaseComponent::GetOwner(); } // This is needed to know which GetOwner() we're calling, since both BaseComponent and IEnemyStateController have a GetOwner()

        void SetState(std::unique_ptr<EnemyCharacterState> newState);

    private:
        std::unique_ptr<EnemyCharacterState> m_currentState;
        FoodPoolComponent* m_pFoodPool{ nullptr };
        MaitaShootComponent* m_pShoot{ nullptr };
        HitboxComponent* m_hitbox{ nullptr };
        PhysicsComponent* m_physics{ nullptr };
        FacingComponent* m_facing{ nullptr };
        RenderComponent* m_render{ nullptr };
        AnimationComponent* m_animation{ nullptr };
    };
}