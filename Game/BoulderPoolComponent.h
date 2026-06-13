#pragma once
#include "BaseComponent.h"
#include <vector>
#include <glm/glm.hpp>

namespace dae
{
    class Scene;
    class Texture2D;

    class BoulderPoolComponent final : public BaseComponent
    {
    public:
        BoulderPoolComponent(GameObject* owner, Scene* scene, Texture2D* boulderTexture, int poolSize = 4);
        ~BoulderPoolComponent() override = default;
        BoulderPoolComponent(const BoulderPoolComponent&) = delete;
        BoulderPoolComponent& operator=(const BoulderPoolComponent&) = delete;
        BoulderPoolComponent(BoulderPoolComponent&&) = delete;
        BoulderPoolComponent& operator=(BoulderPoolComponent&&) = delete;

        void Update(float) override {}
        void FixedUpdate(float) override {}

        GameObject* Acquire(glm::vec3 position, float direction);
        void Release(GameObject* boulder);
        void ReturnAll();

    private:
        std::vector<GameObject*> m_pool;
        int m_nextIndex{ 0 };
    };
}