#include "PhysicsComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "HitboxComponent.h"
#include "ICollisionManager.h"
#include "ServiceLocator.h"
#include "CollisionLayer.h"

namespace dae
{
    PhysicsComponent::PhysicsComponent(GameObject* owner)
        : BaseComponent(owner)
    {
    }

    void PhysicsComponent::FixedUpdate(const float fixedTimeStep)
    {
        if (!m_enabled) return;

        if (!m_hitbox)
        {
            m_hitbox = GetOwner()->GetComponent<HitboxComponent>();
            if (!m_hitbox) return;
        }

        auto* transform = GetOwner()->GetTransform();
        glm::vec3 pos = transform->GetLocalPosition();

        pos.x += m_velocityX * fixedTimeStep;
        transform->SetLocalPosition(pos);
        ResolveWalls(transform);
        m_velocityX = 0.f;

        m_isGrounded = false;
        m_velocityY += k_gravity * fixedTimeStep;
        if (m_velocityY > k_maxFallSpeed)
            m_velocityY = k_maxFallSpeed;

        pos = transform->GetLocalPosition();
        const float prevBottom = pos.y + m_hitbox->GetHeight();
        pos.y += m_velocityY * fixedTimeStep;
        transform->SetLocalPosition(pos);

        ResolvePlatforms(prevBottom, transform);
        ResolveWalls(transform);
    }

    void PhysicsComponent::Jump()
    {
        if (m_isGrounded)
        {
            m_velocityY = -k_jumpSpeed;
            m_isGrounded = false;
        }
    }

    void PhysicsComponent::ResolvePlatforms(const float prevBottom, Transform* transform)
    {
        glm::vec3 pos = transform->GetLocalPosition();

        const float charLeft = pos.x;
        const float charRight = pos.x + m_hitbox->GetWidth();
        float charBottom = pos.y + m_hitbox->GetHeight();

        const auto platforms = ServiceLocator::GetCollisionManager().QueryLayer(CollisionLayer::Platform);
        for (auto* platform : platforms)
        {
            const auto platRect = platform->GetHitBox();
            const float platTop = platRect.y;
            const float platLeft = platRect.x;
            const float platRight = platRect.x + platRect.width;

            if (charRight <= platLeft || charLeft >= platRight)
                continue;

            if (m_velocityY >= 0.f && prevBottom <= platTop && charBottom >= platTop)
            {
                pos.y = platTop - m_hitbox->GetHeight();
                charBottom = pos.y + m_hitbox->GetHeight();
                m_velocityY = 0.f;
                m_isGrounded = true;
                transform->SetLocalPosition(pos);
            }
        }
    }

    void PhysicsComponent::ResolveWalls(Transform* transform)
    {
        glm::vec3 pos = transform->GetLocalPosition();
        bool resolved = false;

        const auto walls = ServiceLocator::GetCollisionManager().QueryLayer(CollisionLayer::Wall);
        for (auto* wall : walls)
        {
            const float charLeft = pos.x;
            const float charRight = pos.x + m_hitbox->GetWidth();
            const float charTop = pos.y;
            const float charBottom = pos.y + m_hitbox->GetHeight();

            const auto  wallRect = wall->GetHitBox();
            const float wallLeft = wallRect.x;
            const float wallRight = wallRect.x + wallRect.width;
            const float wallTop = wallRect.y;
            const float wallBottom = wallRect.y + wallRect.height;

            if (charRight <= wallLeft || charLeft >= wallRight) continue;
            if (charBottom <= wallTop || charTop >= wallBottom) continue;

            const float overlapLeft = charRight - wallLeft;
            const float overlapRight = wallRight - charLeft;
            const float overlapUp = charBottom - wallTop;
            const float overlapDown = wallBottom - charTop;

            const float minX = std::min(overlapLeft, overlapRight);
            const float minY = std::min(overlapUp, overlapDown);

            if (minX <= minY)
            {
                if (overlapLeft < overlapRight)
                    pos.x -= overlapLeft;
                else
                    pos.x += overlapRight;
            }
            else
            {
                /*if (m_velocityY < 0.f)
                {
                    pos.y += overlapDown;
                    m_velocityY = 0.f;
                }
                else
                {
                    pos.y -= overlapUp;
                    m_velocityY = 0.f;
                }*/
            }

            resolved = true;
        }

        if (resolved)
            transform->SetLocalPosition(pos);
    }
}