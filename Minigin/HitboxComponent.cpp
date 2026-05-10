#include "HitboxComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"
#include "ServiceLocator.h"
#include "EventId.h"

namespace dae
{
    HitboxComponent::HitboxComponent(GameObject* owner, float width, float height)
        : BaseComponent(owner), m_width(width), m_height(height), m_hitBox(owner->GetTransform()->GetWorldPosition().x, owner->GetTransform()->GetWorldPosition().y, width, height)
    {
        ServiceLocator::GetCollisionManager().Register(this);
    }

    HitboxComponent::~HitboxComponent()
    {
        ServiceLocator::GetCollisionManager().Unregister(this);
    }

    void HitboxComponent::Update(const float)
    {
        auto pos = GetOwner()->GetTransform()->GetWorldPosition();
        m_hitBox.x = pos.x;
        m_hitBox.y = pos.y;
    }

    bool HitboxComponent::Overlaps(const HitboxComponent& other) const
    {
        return IsOverlapping(m_hitBox, other.GetHitBox());
    }

    void HitboxComponent::BeginOverlap(HitboxComponent* other)
    {
        m_pOverlapPartner = other;
        NotifyObservers(make_sdbm_hash("OnOverlapBegin"));
        m_pOverlapPartner = nullptr;
    }

    void HitboxComponent::EndOverlap(HitboxComponent* other)
    {
        m_pOverlapPartner = other;
        NotifyObservers(make_sdbm_hash("OnOverlapEnd"));
        m_pOverlapPartner = nullptr;
    }
}