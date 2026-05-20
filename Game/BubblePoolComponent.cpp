#include "BubblePoolComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "HitboxComponent.h"
#include "BubbleComponent.h"
#include "RenderComponent.h"
#include "ServiceLocator.h"
#include "CollisionLayer.h"

namespace dae
{
    static constexpr float k_offScreen = -9999.f;
    static constexpr float k_bubbleHitboxSize = 16.f;

    BubblePoolComponent::BubblePoolComponent(GameObject* owner, Scene* scene, Texture2D* bubbleTexture, int poolSize)
        : BaseComponent(owner)
    {
        m_pool.reserve(poolSize);
        for (int i = 0; i < poolSize; ++i)
        {
            auto bubble = std::make_unique<GameObject>();
            auto* raw = bubble.get();

            auto* render = bubble->AddComponent<RenderComponent>();
            render->SetTexture(bubbleTexture);

            auto* hitbox = bubble->AddComponent<HitboxComponent>(k_bubbleHitboxSize, k_bubbleHitboxSize);
            hitbox->SetLayer(CollisionLayer::Bubble);

            bubble->AddComponent<BubbleComponent>(this);

            bubble->GetTransform()->SetLocalPosition({ k_offScreen, k_offScreen, 0.f });
            ServiceLocator::GetCollisionManager().Unregister(hitbox);

            m_pool.push_back(raw);
            scene->Add(std::move(bubble));
        }
    }

    GameObject* BubblePoolComponent::Acquire(glm::vec3 position, float direction)
    {
        const int size = static_cast<int>(m_pool.size());
        for (int i = 0; i < size; ++i)
        {
            const int idx = (m_nextIndex + i) % size;
            auto* bubbleComp = m_pool[idx]->GetComponent<BubbleComponent>();
            if (bubbleComp && !bubbleComp->IsActive())
            {
                m_nextIndex = (idx + 1) % size;
                bubbleComp->Reset(position, direction);
                ServiceLocator::GetCollisionManager().Register(m_pool[idx]->GetComponent<HitboxComponent>());
                return m_pool[idx];
            }
        }
        return nullptr;
    }

    void BubblePoolComponent::Release(GameObject* bubble)
    {
        auto* hitbox = bubble->GetComponent<HitboxComponent>();
        ServiceLocator::GetCollisionManager().Unregister(hitbox);
        bubble->GetTransform()->SetLocalPosition({ k_offScreen, k_offScreen, 0.f });
        bubble->GetComponent<BubbleComponent>()->SetActive(false);
    }
}