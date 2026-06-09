#pragma once
#include <unordered_map>
#include "BaseComponent.h"
#include "EventId.h"

struct SDL_FRect;

namespace dae
{
	class RenderComponent;
	class Texture2D;

	struct AnimationClip
	{
		Texture2D* texture;
		int frameCount;
		int frameWidth;
		int frameHeight;
		float frameDuration;
	};

	class AnimationComponent final : public BaseComponent
	{
	public:
		AnimationComponent(GameObject* owner, RenderComponent* render);
		~AnimationComponent() override = default;
		AnimationComponent(const AnimationComponent&) = delete;
		AnimationComponent& operator=(const AnimationComponent&) = delete;
		AnimationComponent(AnimationComponent&&) = delete;
		AnimationComponent& operator=(AnimationComponent&&) = delete;

		void Update(const float deltaTime) override;
		void FixedUpdate(const float) override {}

		void AddClip(EventId id, AnimationClip clip);
		void Play(EventId id);
		void Pause();

	private:
		RenderComponent* m_render;
		std::unordered_map<EventId, AnimationClip> m_clips;
		EventId m_currentClip{ 0 };
		int m_frameIndex{ 0 };
		float m_frameTimer{ 0.f };
		bool m_paused{ false };

		static constexpr EventId k_noClip{ 0 };
	};
}