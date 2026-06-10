#include "BoulderPoolComponent.h"
#include "BoulderComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "HitboxComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"
#include "CollisionLayer.h"
#include "AnimationComponent.h"
#include "EventId.h"

namespace dae
{
    static constexpr float k_boulderOffScreen = -9999.f;
    static constexpr float k_boulderHitboxSize = 14.f;

    BoulderPoolComponent::BoulderPoolComponent(GameObject* owner, Scene* scene, Texture2D* boulderTexture, int poolSize)
        : BaseComponent(owner)
    {
        m_pool.reserve(poolSize);
        for (int i = 0; i < poolSize; ++i)
        {
            auto boulder = std::make_unique<GameObject>();

            auto* render = boulder->AddComponent<RenderComponent>();
            render->SetTexture(boulderTexture);

            auto* anim = boulder->AddComponent<AnimationComponent>(render);
            anim->AddClip(make_sdbm_hash("roll"), AnimationClip{ boulderTexture, 4, 16, 16, 0.1f });

            auto* hitbox = boulder->AddComponent<HitboxComponent>(k_boulderHitboxSize, k_boulderHitboxSize);
            hitbox->SetLayer(CollisionLayer::Boulder);

            boulder->AddComponent<PhysicsComponent>();
            boulder->AddComponent<BoulderComponent>(this);

            boulder->GetTransform()->SetLocalPosition({ k_boulderOffScreen, k_boulderOffScreen, 0.f });
            ServiceLocator::GetCollisionManager().Unregister(hitbox);
            boulder->GetComponent<PhysicsComponent>()->SetEnabled(false);

            m_pool.push_back(boulder.get());
            scene->Add(std::move(boulder));
        }
    }

    GameObject* BoulderPoolComponent::Acquire(glm::vec3 position, float direction)
    {
        const int size = static_cast<int>(m_pool.size());
        for (int i = 0; i < size; ++i)
        {
            const int idx = (m_nextIndex + i) % size;
            auto* boulderComp = m_pool[idx]->GetComponent<BoulderComponent>();
            if (boulderComp && !boulderComp->IsActive())
            {
                m_nextIndex = (idx + 1) % size;
                boulderComp->Reset(position, direction);
                ServiceLocator::GetCollisionManager().Register(m_pool[idx]->GetComponent<HitboxComponent>());
                return m_pool[idx];
            }
        }
        return nullptr;
    }

    void BoulderPoolComponent::Release(GameObject* boulder)
    {
        ServiceLocator::GetCollisionManager().Unregister(boulder->GetComponent<HitboxComponent>());
        boulder->GetComponent<PhysicsComponent>()->SetEnabled(false);
        boulder->GetComponent<BoulderComponent>()->SetActive(false);
        boulder->GetTransform()->SetLocalPosition({ k_boulderOffScreen, k_boulderOffScreen, 0.f });
    }
}