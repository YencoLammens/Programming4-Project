#include "PoppedState.h"
#include "IEnemyStateController.h"
#include "FoodPoolComponent.h"
#include "HitboxComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "CollisionLayer.h"
#include "Transform.h"
#include "EventId.h"
#include "GameObject.h"
#include <cstdlib>

namespace dae
{
    PoppedState::PoppedState(FoodPoolComponent* foodPool, float riseDuration)
        : m_pFoodPool(foodPool), m_riseDuration(riseDuration)
    {
    }

    void PoppedState::OnEnter(IEnemyStateController* controller)
    {
        m_riseTimer = 0.f;
        m_fallTimer = 0.f;
        m_falling = false;
        m_horizontalDir = (rand() % 2 == 0) ? -1.f : 1.f;

        if (auto* hitbox = controller->GetHitboxComponent()) hitbox->SetLayer(CollisionLayer::None);
        if (auto* physics = controller->GetPhysicsComponent()) physics->SetEnabled(false);
        if (auto* anim = controller->GetAnimationComponent()) anim->Play(make_sdbm_hash("popped"));
    }

    std::unique_ptr<EnemyCharacterState> PoppedState::Update(IEnemyStateController* controller, float deltaTime)
    {
        if (!m_falling)
        {
            m_riseTimer += deltaTime;
            auto* transform = controller->GetOwner()->GetTransform();
            auto pos = transform->GetLocalPosition();
            pos.y -= k_riseSpeed * deltaTime;
            pos.x += m_horizontalDir * k_horizontalSpeed * deltaTime;
            transform->SetLocalPosition(pos);

            if (m_riseTimer >= m_riseDuration)
            {
                m_falling = true;
                if (auto* physics = controller->GetPhysicsComponent())
                    physics->SetEnabled(true);
            }
            return nullptr;
        }

        m_fallTimer += deltaTime;
        if (m_fallTimer <= k_fallGrace)
            return nullptr;

        if (m_fallTimer > k_maxFallTime && !controller->GetOwner()->IsMarkedForDeletion())
        {
            controller->GetOwner()->MarkForDeletion();
            return nullptr;
        }

        auto* physics = controller->GetPhysicsComponent();
        if (physics && physics->IsGrounded() && !controller->GetOwner()->IsMarkedForDeletion())
        {
            if (m_pFoodPool)
                m_pFoodPool->Acquire(controller->GetOwner()->GetTransform()->GetWorldPosition());
            controller->GetOwner()->MarkForDeletion();
        }

        return nullptr;
    }

    void PoppedState::OnExit(IEnemyStateController*)
    {
    }
}