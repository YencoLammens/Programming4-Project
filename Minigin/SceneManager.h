#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"
#include <functional>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();

		void Update(const float deltaTime);
		void FixedUpdate(const float fixedTimeStep);
		void Render();

		void RemoveFlaggedObjects();
		void SetDeletionPending() { m_hasDeletionsPending = true; }

		void RequestTransition(std::function<void()> transition);
		void FlushPendingTransition();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};
		std::function<void()> m_pendingTransition;
		bool m_hasDeletionsPending = false;
	};
}
