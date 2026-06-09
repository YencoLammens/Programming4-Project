#include "PickupComponent.h"
#include "HitboxComponent.h"
#include "FoodPoolComponent.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionLayer.h"
#include "EventId.h"

namespace dae
{
    PickupComponent::PickupComponent(GameObject* owner, HitboxComponent* hitbox, FoodPoolComponent* pool, int pointValue)
        : BaseComponent(owner), m_pHitbox(hitbox), m_pPool(pool), m_pointValue(pointValue)
    {
        m_pHitbox->AddObserver(this);
    }

    PickupComponent::~PickupComponent()
    {
        if (m_pHitbox)
            m_pHitbox->RemoveObserver(this);
    }

    void PickupComponent::Notify(EventId event)
    {
        if (event != make_sdbm_hash("OnOverlapBegin")) return;
        if (!m_isActive || !m_pHitbox) return;

        auto* partner = m_pHitbox->GetOverlapPartner();
        if (!partner || partner->GetLayer() != CollisionLayer::Player) return;

        if (auto* score = partner->GetOwner()->GetComponent<ScoreComponent>())
            score->AddPoints(m_pointValue);

        m_pPool->Release(GetOwner());
    }

    void PickupComponent::Activate(glm::vec3 position)
    {
        GetOwner()->GetTransform()->SetLocalPosition(position);
        m_isActive = true;
    }
}