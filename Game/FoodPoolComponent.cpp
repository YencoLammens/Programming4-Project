#include "FoodPoolComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "HitboxComponent.h"
#include "PickupComponent.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"
#include "CollisionLayer.h"

namespace dae
{
    static constexpr float k_foodOffScreen = -9999.f;
    static constexpr float k_pickupHitboxSize = 16.f;

    FoodPoolComponent::FoodPoolComponent(GameObject* owner, Scene* scene, Texture2D* texture, int pointValue, int poolSize)
        : BaseComponent(owner)
    {
        m_pool.reserve(poolSize);
        for (int i = 0; i < poolSize; ++i)
        {
            auto pickup = std::make_unique<GameObject>();

            auto* render = pickup->AddComponent<RenderComponent>();
            render->SetTexture(texture);

            auto* hitbox = pickup->AddComponent<HitboxComponent>(k_pickupHitboxSize, k_pickupHitboxSize);
            hitbox->SetLayer(CollisionLayer::Food);

            pickup->AddComponent<PickupComponent>(hitbox, this, pointValue);

            pickup->GetTransform()->SetLocalPosition({ k_foodOffScreen, k_foodOffScreen, 0.f });
            ServiceLocator::GetCollisionManager().Unregister(hitbox);

            m_pool.push_back(pickup.get());
            scene->Add(std::move(pickup));
        }
    }

    GameObject* FoodPoolComponent::Acquire(glm::vec3 position)
    {
        const int size = static_cast<int>(m_pool.size());
        for (int i = 0; i < size; ++i)
        {
            const int idx = (m_nextIndex + i) % size;
            auto* pickupComp = m_pool[idx]->GetComponent<PickupComponent>();
            if (pickupComp && !pickupComp->IsActive())
            {
                m_nextIndex = (idx + 1) % size;
                pickupComp->Activate(position);
                ServiceLocator::GetCollisionManager().Register(m_pool[idx]->GetComponent<HitboxComponent>());
                return m_pool[idx];
            }
        }
        return nullptr;
    }

    void FoodPoolComponent::Release(GameObject* pickup)
    {
        auto* hitbox = pickup->GetComponent<HitboxComponent>();
        ServiceLocator::GetCollisionManager().Unregister(hitbox);
        pickup->GetTransform()->SetLocalPosition({ k_foodOffScreen, k_foodOffScreen, 0.f });
        pickup->GetComponent<PickupComponent>()->SetActive(false);
    }
}