#pragma once
#include "BaseComponent.h"
#include <vector>
#include <glm/glm.hpp>

namespace dae
{
    class Scene;
    class Texture2D;

    class FoodPoolComponent final : public BaseComponent
    {
    public:
        FoodPoolComponent(GameObject* owner, Scene* scene, Texture2D* texture, int pointValue, int poolSize = 4);
        ~FoodPoolComponent() override = default;
        FoodPoolComponent(const FoodPoolComponent&) = delete;
        FoodPoolComponent& operator=(const FoodPoolComponent&) = delete;
        FoodPoolComponent(FoodPoolComponent&&) = delete;
        FoodPoolComponent& operator=(FoodPoolComponent&&) = delete;

        void Update(float) override {}
        void FixedUpdate(float) override {}

        GameObject* Acquire(glm::vec3 position);
        void Release(GameObject* pickup);

    private:
        std::vector<GameObject*> m_pool;
        int m_nextIndex{ 0 };
    };
}