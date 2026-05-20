#include "EnemyBubbledObserver.h"
#include "HitboxComponent.h"
#include "CharacterStateComponent.h"
#include "BubbledState.h"
#include "CollisionLayer.h"
#include "EventId.h"

namespace dae
{
    EnemyBubbledObserver::EnemyBubbledObserver(GameObject* owner, HitboxComponent* hitbox, CharacterStateComponent* stateComp)
        : BaseComponent(owner), m_pHitbox(hitbox), m_pStateComp(stateComp)
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
        if (event == make_sdbm_hash("OnOverlapBegin"))
        {
            auto* partner = m_pHitbox->GetOverlapPartner();
            if (partner && partner->GetLayer() == CollisionLayer::Bubble)
                m_pStateComp->SetState(std::make_unique<BubbledState>());
        }
    }
}