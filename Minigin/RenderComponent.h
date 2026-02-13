#pragma once

#include <memory>
#include <SDL3/SDL.h>
#include <glm/vec3.hpp>
#include "BaseComponent.h"
#include "Texture2D.h"
#include "IRenderable.h"


namespace dae
{
	class RenderComponent : public BaseComponent, public IRenderable
	{
	public:
		RenderComponent(GameObject* owner);
		~RenderComponent() override;
		RenderComponent(const RenderComponent&) = delete;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent(RenderComponent&&) = delete;
		RenderComponent& operator=(RenderComponent&&) = delete;
		virtual void Update(float deltaTime) override;
		virtual void FixedUpdate(float fixedTimeStep) override;
		virtual void Render() const;

		void SetTexture(Texture2D* texture);
		void SetEnabled(bool enabled) { m_enabled = enabled; }

	private:
		Texture2D* m_texture;
		SDL_Rect m_sourceRect{};
		glm::vec3 m_position;

		bool m_useSourceRect{ false };
		bool m_enabled{ true };
	};
}