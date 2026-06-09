#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <glm/vec3.hpp>
#include "BaseComponent.h"
#include "Texture2D.h"


namespace dae
{
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(GameObject* owner);
		~RenderComponent() override;
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator=(RenderComponent&&) = delete;
		virtual void Update(const float deltaTime) override;
		virtual void FixedUpdate(const float fixedTimeStep) override;
		virtual void Render() const override;

		void SetTexture(Texture2D* texture);
		void SetEnabled(bool enabled) { m_enabled = enabled; }
		void SetFlipX(bool flip) { m_flipX = flip; }
		void SetSourceRect(const SDL_FRect& rect) { m_sourceRect = rect; m_useSourceRect = true; }
		void ClearSourceRect() { m_useSourceRect = false; }
	private:
		Texture2D* m_texture;
		SDL_FRect m_sourceRect{};
		glm::vec3 m_position;

		bool m_useSourceRect{ false };
		bool m_enabled{ true };
		bool m_flipX{ false };
	};
}