#include "RenderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

dae::RenderComponent::RenderComponent(GameObject* owner)
	: BaseComponent(owner), m_position{ 0, 0, 0 }
{
		//auto& renderer = Renderer::GetInstance();


}

dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Update(float)
{
	m_position = GetOwner()->GetTransform()->GetWorldPosition();
}

void dae::RenderComponent::FixedUpdate(float)
{
}

//Orignal method
//void dae::RenderComponent::Render() const
//{
//	
//
//	if (m_texture && m_enabled)
//	{
//		auto* transform = GetOwner()->GetTransform();
//		const auto pos = transform->GetWorldPosition();
//
//		auto* spriteState = GetOwner()->GetComponent<SpriteRenderStateComponent>();
//		if (spriteState)
//		{
//			Renderer::GetInstance().RenderTexture(
//				*m_texture,
//				pos.x, pos.y,
//				spriteState->GetRotation(),
//				spriteState->GetFlipX()
//			);
//		}
//		else
//		{
//			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
//		}
//	}
//}


////Animated method
//void dae::RenderComponent::Render() const
//{
//	if (m_texture && m_enabled)
//	{
//		auto* transform = GetOwner()->GetTransform();
//		const auto pos = transform->GetWorldPosition();
//
//		// Build destination rect using the position and texture size
//		SDL_Rect dstRect{};
//		dstRect.x = static_cast<int>(pos.x);
//		dstRect.y = static_cast<int>(pos.y);
//		dstRect.w = static_cast<int>(m_sourceRect.w);
//		dstRect.h = static_cast<int>(m_sourceRect.h);
//
//		Renderer::GetInstance().RenderTexture(*m_texture, m_sourceRect, dstRect);
//	}
//}


void dae::RenderComponent::Render() const
{
	if (!m_texture || !m_enabled) return;

	auto* transform = GetOwner()->GetTransform();
	const auto pos = transform->GetWorldPosition();

	// Default static rendering
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}


void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_texture = texture;
}

//void dae::RenderComponent::Update()
//{
//    //if (m_needsUpdate)
//    //{
//    //    const SDL_Color color = { 255, 255, 255, 255 }; // only white text is supported now
//    //    const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
//    //    if (surf == nullptr)
//    //    {
//    //        throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
//    //    }
//    //    auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
//    //    if (texture == nullptr)
//    //    {
//    //        throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
//    //    }
//    //    SDL_FreeSurface(surf);
//    //    m_textTexture = std::make_shared<Texture2D>(texture);
//    //    m_needsUpdate = false;
//
//    //}
//    //if (m_owner)
//    //{
//    //    m_position = m_owner->GetWorldPosition() * deltaTime;
//    //}
//}