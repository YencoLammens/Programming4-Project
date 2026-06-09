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
	const auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	if (m_useSourceRect)
	{
		const SDL_FlipMode flip = m_flipX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, m_sourceRect, flip);
	}
	else if (m_flipX)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		// Default static rendering
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::RenderComponent::SetTexture(Texture2D* texture)
{
	m_texture = texture;
}

