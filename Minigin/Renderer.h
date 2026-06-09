#pragma once
#include <SDL3/SDL.h>
#include <glm/vec2.hpp>
#include "Singleton.h"
#include "RenderComponent.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
		glm::vec2 m_cameraOffset{ 0.f, 0.f };
		SDL_Rect m_clipRect{};
		bool m_useClipRect{ false };

	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float x, float y, SDL_FlipMode flip) const;
		void RenderTexture(const Texture2D& texture, float x, float y, const SDL_FRect& srcRect) const;
		void RenderTexture(const Texture2D& texture, float x, float y, const SDL_FRect& srcRect, SDL_FlipMode flip) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		void SetCameraOffset(const glm::vec2& offset) { m_cameraOffset = offset; }
		void SetCameraClipRect(const SDL_Rect& rect) { m_clipRect = rect; m_useClipRect = true; }
		void ClearCameraClipRect() { m_useClipRect = false; }
		const glm::vec2& GetCameraOffset() const { return m_cameraOffset; }

		void SetLogicalPresentation(int w, int h);

	private:
	};
}