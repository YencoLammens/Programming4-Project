#pragma once
#include <memory>
#include "BaseComponent.h"
#include "ZenChanCharacterState.h"

namespace dae
{
    class HitboxComponent;
    class PhysicsComponent;
    class FacingComponent;
    class RenderComponent;
    class AnimationComponent;

    class ZenChanStateController final : public BaseComponent
    {
    public:
        ZenChanStateController(GameObject* owner, std::unique_ptr<ZenChanCharacterState> initialState);
        ~ZenChanStateController() override = default;
        ZenChanStateController(const ZenChanStateController&) = delete;
        ZenChanStateController& operator=(const ZenChanStateController&) = delete;
        ZenChanStateController(ZenChanStateController&&) = delete;
        ZenChanStateController& operator=(ZenChanStateController&&) = delete;

        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void OnBubbled();
        void OnPopped();

        HitboxComponent* GetHitboxComponent() const { return m_hitbox; }
        PhysicsComponent* GetPhysicsComponent() const { return m_physics; }
        FacingComponent* GetFacingComponent() const { return m_facing; }
        RenderComponent* GetRenderComponent() const { return m_render; }
        AnimationComponent* GetAnimationComponent() const { return m_animation; }

        void SetState(std::unique_ptr<ZenChanCharacterState> newState);

    private:
        std::unique_ptr<ZenChanCharacterState> m_currentState;

        HitboxComponent* m_hitbox{ nullptr };
        PhysicsComponent* m_physics{ nullptr };
        FacingComponent* m_facing{ nullptr };
        RenderComponent* m_render{ nullptr };
        AnimationComponent* m_animation{ nullptr };
    };
}