#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}

	// TODO: move into LateUpdate() once added, same as component cleanup
	if (m_hasDeletionsPending)
	{
		RemoveFlaggedObjects();
		m_hasDeletionsPending = false;
	}
}

void dae::SceneManager::FixedUpdate(const float fixedTimeStep)
{
	for(auto& scene : m_scenes)
	{
		scene->FixedUpdate(fixedTimeStep);
	}
}


void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RemoveFlaggedObjects()
{
	if (!m_hasDeletionsPending) return; //prevent it from unecessarily looping through everything if no deletion is necessary

	for (auto& scene : m_scenes)
	{
		scene->RemoveFlaggedObjects();
	}

	m_hasDeletionsPending = false;
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}
