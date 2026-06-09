#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include <cassert>
#include <SDL3/SDL.h>

namespace dae
{
	AnimationComponent::AnimationComponent(GameObject* owner, RenderComponent* render)
		: BaseComponent(owner), m_render(render)
	{
		assert(m_render != nullptr);
	}

	void AnimationComponent::Update(const float deltaTime)
	{
		if (m_paused || m_currentClip == k_noClip) return;

		const auto it = m_clips.find(m_currentClip);
		if (it == m_clips.end()) return;

		const auto& clip = it->second;

		m_frameTimer += deltaTime;
		if (m_frameTimer >= clip.frameDuration)
		{
			m_frameTimer -= clip.frameDuration;
			m_frameIndex = (m_frameIndex + 1) % clip.frameCount;
		}

		const SDL_FRect src
		{
			static_cast<float>(m_frameIndex * clip.frameWidth),
			0.f,
			static_cast<float>(clip.frameWidth),
			static_cast<float>(clip.frameHeight)
		};
		m_render->SetSourceRect(src);
	}

	void AnimationComponent::AddClip(EventId id, AnimationClip clip)
	{
		m_clips[id] = clip;
	}

	void AnimationComponent::Play(EventId id)
	{
		if (id == m_currentClip && !m_paused) return;

		m_paused = false;
		m_currentClip = id;
		m_frameIndex = 0;
		m_frameTimer = 0.f;

		const auto it = m_clips.find(id);
		if (it == m_clips.end()) return;

		const auto& clip = it->second;
		m_render->SetTexture(clip.texture);

		const SDL_FRect src{ 0.f, 0.f, static_cast<float>(clip.frameWidth), static_cast<float>(clip.frameHeight) };
		m_render->SetSourceRect(src);
	}

	void AnimationComponent::Pause()
	{
		m_paused = true;
	}
}