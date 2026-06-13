#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class CameraComponent final : public BaseComponent
	{
	public:
		CameraComponent(GameObject* owner, float viewportWidth, float viewportHeight, float levelWidth, float levelHeight);
		~CameraComponent() override;
		CameraComponent(const CameraComponent&) = delete;
		CameraComponent& operator=(const CameraComponent&) = delete;
		CameraComponent(CameraComponent&&) = delete;
		CameraComponent& operator=(CameraComponent&&) = delete;

		void Update(float deltaTime) override;
		void FixedUpdate(float fixedTimeStep) override;

	private:
		float m_viewportWidth;
		float m_viewportHeight;
		float m_levelWidth;
		float m_levelHeight;
		std::vector<GameObject*> m_targets;
	};
}