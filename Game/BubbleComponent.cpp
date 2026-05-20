#include "BubbleComponent.h"
#include "HitboxComponent.h"
#include "BubblePoolComponent.h"
#include "CollisionLayer.h"
#include "EventId.h"
#include "GameObject.h"
#include "Transform.h"

namespace dae
{
    BubbleComponent::BubbleComponent(GameObject* owner, BubblePoolComponent* pool)
        : BaseComponent(owner), m_pool(pool)
    {
        m_transform = GetOwner()->GetTransform();
        m_hitbox = GetOwner()->GetComponent<HitboxComponent>();
        if (m_hitbox)
            m_hitbox->AddObserver(this);
    }

    BubbleComponent::~BubbleComponent()
    {
        if (m_hitbox)
            m_hitbox->RemoveObserver(this);
    }

    void BubbleComponent::Update(float deltaTime)
    {
        if (!m_active) return;

        if (m_pendingRelease)
        {
            m_pendingRelease = false;
            m_pool->Release(GetOwner());
            return;
        }

        m_lifetimeTimer += deltaTime;
        if (m_lifetimeTimer >= k_lifetime)
        {
            m_pool->Release(GetOwner());
            return;
        }

        m_travelTimer += deltaTime;
        glm::vec3 pos = m_transform->GetLocalPosition();

        if (m_traveling)
        {
            pos += m_velocity * deltaTime;
            if (m_travelTimer >= k_travelDuration)
                m_traveling = false;
        }
        else
        {
            pos.y -= k_floatSpeed * deltaTime;
        }

        m_transform->SetLocalPosition(pos);
    }

    void BubbleComponent::Notify(EventId event)
    {
        if (!m_active) return;
        if (event == make_sdbm_hash("OnOverlapBegin"))
        {
            auto* partner = m_hitbox->GetOverlapPartner();
            if (partner && partner->GetLayer() == CollisionLayer::Enemy)
                m_pendingRelease = true;
        }
    }

    void BubbleComponent::Reset(glm::vec3 position, float direction)
    {
        m_travelTimer = 0.f;
        m_lifetimeTimer = 0.f;
        m_pendingRelease = false;
        m_traveling = true;
        m_active = true;
        m_velocity = { direction * k_travelSpeed, 0.f, 0.f };
        m_transform->SetLocalPosition(position);
    }
}