#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

dae::RenderComponent::RenderComponent(GameObject* owner)
	: BaseComponent(owner), m_texture(nullptr), m_position{ 0, 0, 0 }
{
		//auto& renderer = Renderer::GetInstance();


}

dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Update(float)
{
	
}

void dae::RenderComponent::FixedUpdate(float)
{
}

void dae::RenderComponent::Render() const
{
	if (!m_texture || !m_enabled) return;

	auto* transform = GetOwner()->GetTransform();
	const auto pos = transform->GetWorldPosition();

	// Default static rendering
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::RenderComponent::SetTexture(Texture2D* texture)
{
	m_texture = texture;
}

