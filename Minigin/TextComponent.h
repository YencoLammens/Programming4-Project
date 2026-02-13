#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "BaseComponent.h"
#include "IRenderable.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent, public IRenderable
	{
	public:
		TextComponent(GameObject* owner, const std::string& text, Font* font);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float deltaTime) override;
		void FixedUpdate(float) override {};
		void Render() const;

		void SetText(const std::string& text);

		
	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::unique_ptr<Texture2D> m_textTexture;
		SDL_Color m_color{ 255, 255, 255, 255 };
	};
}
