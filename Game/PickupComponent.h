#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include <glm/glm.hpp>

namespace dae
{
    class HitboxComponent;
    class FoodPoolComponent;

    class PickupComponent final : public BaseComponent, public Observer
    {
    public:
        PickupComponent(GameObject* owner, HitboxComponent* hitbox, FoodPoolComponent* pool, int pointValue);
        ~PickupComponent() override;
        PickupComponent(const PickupComponent&) = delete;
        PickupComponent& operator=(const PickupComponent&) = delete;
        PickupComponent(PickupComponent&&) = delete;
        PickupComponent& operator=(PickupComponent&&) = delete;

        void Update(float) override {}
        void FixedUpdate(float) override {}
        void Notify(EventId event) override;
        void OnSubjectDestroyed() override { m_pHitbox = nullptr; }

        void Activate(glm::vec3 position);
        bool IsActive() const { return m_isActive; }
        void SetActive(bool active) { m_isActive = active; }

    private:
        HitboxComponent* m_pHitbox;
        FoodPoolComponent* m_pPool;
        int m_pointValue;
        bool m_isActive{ false };
    };
}