#pragma once
#include <memory>

namespace dae
{
    class HitboxComponent;
    class PhysicsComponent;
    class FacingComponent;
    class RenderComponent;
    class AnimationComponent;
    class EnemyCharacterState;
    class GameObject;

    class IEnemyStateController
    {
    public:
        virtual ~IEnemyStateController() = default;
        IEnemyStateController(const IEnemyStateController&) = delete;
        IEnemyStateController& operator=(const IEnemyStateController&) = delete;
        IEnemyStateController(IEnemyStateController&&) = delete;
        IEnemyStateController& operator=(IEnemyStateController&&) = delete;

        virtual void OnBubbled() = 0;
        virtual void OnPopped() = 0;

        virtual HitboxComponent* GetHitboxComponent() const = 0;
        virtual PhysicsComponent* GetPhysicsComponent() const = 0;
        virtual FacingComponent* GetFacingComponent() const = 0;
        virtual RenderComponent* GetRenderComponent() const = 0;
        virtual AnimationComponent* GetAnimationComponent() const = 0;

        virtual GameObject* GetOwner() const = 0; //The states call controller->GetOwner() directly

    protected:
        IEnemyStateController() = default;
    };
}