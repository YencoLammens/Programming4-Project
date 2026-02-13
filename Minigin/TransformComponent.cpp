#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* owner)
	:BaseComponent(owner), m_localPosition(0, 0, 0), m_worldPosition(0, 0, 0), m_positionIsDirty(false)
{

}

const glm::vec3& dae::TransformComponent::GetLocalPosition() const
{
	return m_localPosition;
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	SetPositionDirty();
}

void dae::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	SetLocalPosition(glm::vec3(x, y, z));
}

const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_positionIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_worldPosition;
}

void dae::TransformComponent::UpdateWorldPosition()
{
	if (m_positionIsDirty)
	{
		if (GetOwner()->GetParent() == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = GetOwner()->GetParent()->GetTransform()->GetWorldPosition() + m_localPosition;
	}
	m_positionIsDirty = false;
}

bool dae::TransformComponent::IsPositionDirty()
{
	return m_positionIsDirty;
}

void dae::TransformComponent::SetPositionDirty()
{
	m_positionIsDirty = true;
	for (auto& child : GetOwner()->GetChildren())
	{
		child->GetTransform()->SetPositionDirty();
	}
}

//void dae::TransformComponent::SetRotation(float angleDegrees)
//{
//	m_rotationDegrees = angleDegrees;
//}
//
//float dae::TransformComponent::GetRotation() const
//{
//	return m_rotationDegrees;
//}

void dae::TransformComponent::Update(float)
{
	//m_localPosition += deltaTime;
}	

void dae::TransformComponent::FixedUpdate(float)
{
}