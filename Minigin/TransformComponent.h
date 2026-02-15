#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class TransformComponent final: public BaseComponent
	{
	public:
		TransformComponent(GameObject* parent);
		const glm::vec3& GetLocalPosition() const;
		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(float x, float y, float z);
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();
		bool IsPositionDirty();
		void SetPositionDirty();

		/*void SetRotation(float angleDegrees);
		float GetRotation() const;*/

		void Update(const float deltaTime) override;
		void FixedUpdate(const float fixedTimeStep) override;


	private:
		glm::vec3 m_localPosition;
		glm::vec3 m_worldPosition;
		bool m_positionIsDirty = false;
		//float m_rotationDegrees{ 0.0f };
	};
}
