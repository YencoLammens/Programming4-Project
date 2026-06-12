#include "EnemyBubbledObserver.h"
#include "HitboxComponent.h"
#include "IEnemyStateController.h"
#include "CollisionLayer.h"
#include "EventId.h"
#include "GameObject.h"
#include "ServiceLocator.h"

namespace dae
{
    EnemyBubbledObserver::EnemyBubbledObserver(GameObject* owner, HitboxComponent* hitbox, IEnemyStateController* stateController)
        : BaseComponent(owner), m_pHitbox(hitbox), m_pStateController(stateController)
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
            ServiceLocator::GetSoundSystem().Play(8, 0.5f);
            return;
        }

        if (ownLayer == CollisionLayer::BubbledEnemy && partnerLayer == CollisionLayer::Player)
        {
            m_pStateController->OnPopped();
            ServiceLocator::GetSoundSystem().Play(1, 0.5f);
			return;
        }
            
    }
}