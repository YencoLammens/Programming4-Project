#include "CameraComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

dae::CameraComponent::CameraComponent(GameObject* owner, float viewportWidth, float viewportHeight, float levelWidth, float levelHeight)
	: BaseComponent(owner), m_viewportWidth(viewportWidth), m_viewportHeight(viewportHeight), m_levelWidth(levelWidth), m_levelHeight(levelHeight)
{
	Renderer::GetInstance().SetLogicalPresentation(static_cast<int>(m_levelWidth), static_cast<int>(m_levelHeight));
	Renderer::GetInstance().ClearCameraClipRect();
}

dae::CameraComponent::~CameraComponent()
{
	Renderer::GetInstance().SetLogicalPresentation(static_cast<int>(m_viewportWidth), static_cast<int>(m_viewportHeight));	
	Renderer::GetInstance().SetCameraOffset({ 0.f, 0.f });
}

void dae::CameraComponent::Update(float)
{
	const glm::vec3 levelOrigin = GetOwner()->GetTransform()->GetWorldPosition();
	Renderer::GetInstance().SetCameraOffset({ -levelOrigin.x, -levelOrigin.y });
}

void dae::CameraComponent::FixedUpdate(float)
{
}