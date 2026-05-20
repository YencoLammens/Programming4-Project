#pragma once
#include "BaseComponent.h"
#include <vector>
#include <glm/glm.hpp>

namespace dae
{
    class Scene;
    class Texture2D;

    class BubblePoolComponent final : public BaseComponent
    {
    public:
        BubblePoolComponent(GameObject* owner, Scene* scene, Texture2D* bubbleTexture, int poolSize = 8);
        ~BubblePoolComponent() override = default;
        BubblePoolComponent(const BubblePoolComponent&) = delete;
        BubblePoolComponent& operator=(const BubblePoolComponent&) = delete;
        BubblePoolComponent(BubblePoolComponent&&) = delete;
        BubblePoolComponent& operator=(BubblePoolComponent&&) = delete;

        void Update(float) override {}
        void FixedUpdate(float) override {}

        GameObject* Acquire(glm::vec3 position, float direction);
        void Release(GameObject* bubble);

    private:
        std::vector<GameObject*> m_pool;
        int m_nextIndex{ 0 };
    };
}