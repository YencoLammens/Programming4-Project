#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
    class RotatorComponent final : public BaseComponent
    {
    public:
        explicit RotatorComponent(GameObject* owner, float radius = 100.f, float speed = 1.f, glm::vec3 center = {0,0,0});
        virtual ~RotatorComponent() override = default;

        RotatorComponent(const RotatorComponent& other) = delete;
        RotatorComponent(RotatorComponent&& other) = delete;
        RotatorComponent& operator=(const RotatorComponent& other) = delete;
        RotatorComponent& operator=(RotatorComponent&& other) = delete;

        void Update(const float deltaTime) override;
        void FixedUpdate(const float) override {};

    private:
        float m_radius;
        float m_speed;
        float m_angle{ 0.f };
        glm::vec3 m_center;
    };
}
