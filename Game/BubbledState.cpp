#include "BubbledState.h"
#include "WanderingState.h"
#include "IEnemyStateController.h"
#include "HitboxComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "CollisionLayer.h"
#include "Transform.h"
#include "EventId.h"
#include "GameObject.h"

namespace dae
{
    BubbledState::BubbledState(float duration)
        : m_duration(duration)
    {
    }

    void BubbledState::OnEnter(IEnemyStateController* controller)
    {
        m_timer = 0.f;
        if (auto* hitbox = controller->GetHitboxComponent())  hitbox->SetLayer(CollisionLayer::BubbledEnemy);
        if (auto* physics = controller->GetPhysicsComponent()) physics->SetEnabled(false);
        if (auto* anim = controller->GetAnimationComponent()) anim->Play(make_sdbm_hash("bubbled"));
    }

    std::unique_ptr<EnemyCharacterState> BubbledState::Update(IEnemyStateController* controller, float deltaTime)
    {
        m_timer += deltaTime;

        auto* transform = controller->GetOwner()->GetTransform();
        auto pos = transform->GetLocalPosition();
        pos.y -= k_floatSpeed * deltaTime;
        transform->SetLocalPosition(pos);

        if (m_timer >= m_duration)
            return std::make_unique<WanderingState>();
        return nullptr;
    }

    void BubbledState::OnExit(IEnemyStateController* controller)
    {
        if (auto* hitbox = controller->GetHitboxComponent())  hitbox->SetLayer(CollisionLayer::Enemy);
        if (auto* physics = controller->GetPhysicsComponent()) physics->SetEnabled(true);
    }
}