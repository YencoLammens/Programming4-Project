#pragma once
#include "Command.h"
#include <glm/glm.hpp>

namespace dae
{
	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float speed);

		void Execute(float deltaTime) override;

	private:
		glm::vec3 m_direction;
		float m_speed;
	};
}