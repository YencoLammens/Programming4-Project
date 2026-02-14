#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();

		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render();

		void RemoveFlaggedObjects();
		void SetDeletionPending() { m_hasDeletionsPending = true; }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};
		bool m_hasDeletionsPending = false;
	};
}
