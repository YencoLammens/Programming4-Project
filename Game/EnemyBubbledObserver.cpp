#include "EnemyBubbledObserver.h"
#include "HitboxComponent.h"
#include "ZenChanStateController.h"
#include "FoodPoolComponent.h"
#include "BubbledState.h"
#include "PoppedState.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionLayer.h"
#include "EventId.h"

namespace dae
{
    EnemyBubbledObserver::EnemyBubbledObserver(GameObject* owner, HitboxComponent* hitbox, ZenChanStateController* stateController, FoodPoolComponent* foodPool)
        : BaseComponent(owner), m_pHitbox(hitbox), m_pStateController(stateController), m_pFoodPool(foodPool)
    {
        m_pHitbox->AddObserver(this);
    }

    EnemyBubbledObserver::~EnemyBubbledObserver()
    {
        if (m_pHitbox)
            m_pHitbox->RemoveObserver(this);
    }

    void EnemyBubbledObserver::Notify(EventId event)
    {
        if (event != make_sdbm_hash("OnOverlapBegin")) return;

        auto* partner = m_pHitbox->GetOverlapPartner();
        if (!partner) return;

        const CollisionLayer ownLayer = m_pHitbox->GetLayer();
        const CollisionLayer partnerLayer = partner->GetLayer();

        if (ownLayer == CollisionLayer::Enemy && partnerLayer == CollisionLayer::Bubble)
        {
            m_pStateController->OnBubbled();
            return;
        }

        if (ownLayer == CollisionLayer::BubbledEnemy && partnerLayer == CollisionLayer::Player)
        {
            const auto position = m_pHitbox->GetOwner()->GetTransform()->GetWorldPosition();
            m_pFoodPool->Acquire(position);
            m_pStateController->OnPopped();
        }
    }
}