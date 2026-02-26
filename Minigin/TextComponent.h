#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL.h>
#include "GameObject.h"
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class RenderComponent;
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(GameObject* owner, const std::string& text, Font* font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(const float deltaTime) override;
		void FixedUpdate(const float) override {};
		void Render() const override {};

		void SetText(const std::string& text);

		
	private:
		bool m_needsUpdate;
		std::string m_text;
		Font* m_font;
		std::unique_ptr<Texture2D> m_textTexture;
		RenderComponent* m_renderComponent;
		SDL_Color m_color{ 255, 255, 255, 255 };
	};
}
