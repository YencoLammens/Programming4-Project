#include "BoulderComponent.h"
#include "BoulderPoolComponent.h"
#include "HitboxComponent.h"
#include "PhysicsComponent.h"
#include "ServiceLocator.h"
#include "ICollisionManager.h"
#include "CollisionLayer.h"
#include "EventId.h"
#include "GameObject.h"
#include "Transform.h"
#include "AnimationComponent.h"

namespace dae
{
    BoulderComponent::BoulderComponent(GameObject* owner, BoulderPoolComponent* pool)
        : BaseComponent(owner), m_pool(pool)
    {
        m_transform = GetOwner()->GetTransform();
        m_hitbox = GetOwner()->GetComponent<HitboxComponent>();
        if (m_hitbox)
            m_hitbox->AddObserver(this);
    }

    BoulderComponent::~BoulderComponent()
    {
        if (m_hitbox)
            m_hitbox->RemoveObserver(this);
    }

    void BoulderComponent::Update(float deltaTime)
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
            m_pool->Release(GetOwner());
    }

    void BoulderComponent::FixedUpdate(float)
    {
        if (!m_active || m_pendingRelease) return;

        if (!m_physics)
            m_physics = GetOwner()->GetComponent<PhysicsComponent>();

        if (m_hitbox)
        {
            const auto rect = m_hitbox->GetHitBox();
            const auto walls = ServiceLocator::GetCollisionManager().QueryLayer(CollisionLayer::Wall);
            for (const auto* wall : walls)
            {
                const auto w = wall->GetHitBox();
                if (rect.y + rect.height <= w.y || rect.y >= w.y + w.height) continue;
                if (m_direction > 0.f && rect.x + rect.width + k_wallMargin >= w.x && rect.x < w.x)
                {
                    m_direction = -1.f;
                    break;
                }
                else if (m_direction < 0.f && rect.x - k_wallMargin <= w.x + w.width && rect.x + rect.width > w.x + w.width)
                {
                    m_direction = 1.f;
                    break;
                }
            }
        }

        if (m_physics)
            m_physics->SetHorizontalVelocity(m_direction * k_speed);
    }

    void BoulderComponent::Notify(EventId event)
    {
        if (!m_active) return;
        if (event != make_sdbm_hash("OnOverlapBegin")) return;

        auto* partner = m_hitbox->GetOverlapPartner();
        if (partner && partner->GetLayer() == CollisionLayer::Player)
            m_pendingRelease = true;
    }

    void BoulderComponent::Reset(glm::vec3 position, float direction)
    {
        m_direction = direction;
        m_lifetimeTimer = 0.f;
        m_pendingRelease = false;
        m_active = true;
        m_transform->SetLocalPosition(position);

        if (!m_physics)
            m_physics = GetOwner()->GetComponent<PhysicsComponent>();
        if (m_physics)
        {
            m_physics->ResetVelocity();
            m_physics->SetEnabled(true);
        }
        if (!m_animation)
            m_animation = GetOwner()->GetComponent<AnimationComponent>();
        if (m_animation)
            m_animation->Play(make_sdbm_hash("roll"));
    }
}