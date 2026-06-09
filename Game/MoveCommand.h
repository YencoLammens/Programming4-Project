#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
    class RenderComponent;
    class FacingComponent;
    class PhysicsComponent;
    class Transform;
    class PlayerStateController;

    class MoveCommand final : public GameObjectCommand
    {
    public:
        MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float speed, PlayerStateController* stateController = nullptr);
        void Execute(float deltaTime) override;

    private:
        glm::vec3 m_direction;
        float m_speed;
        RenderComponent* m_render{ nullptr };
        FacingComponent* m_facing{ nullptr };
        PhysicsComponent* m_physics{ nullptr };
		Transform* m_transform{ nullptr };
        PlayerStateController* m_stateController{ nullptr };
    };
}