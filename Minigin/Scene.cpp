#include <algorithm>
#include "Scene.h"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject>&& object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[&object](const auto& ptr) { return ptr.get() == &object; }
		),
		m_objects.end()
	);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::RemoveFlaggedObjects()
{
	for (auto& object : m_objects)
	{
		object->RemoveFlaggedComponents();
	}

	//Reverse iteration
	for (int idx = static_cast<int>(m_objects.size()) - 1; idx >= 0; --idx)
	{
		if (m_objects[idx]->IsMarkedForDeletion())
		{
			m_objects.erase(m_objects.begin() + idx);
		}
	}
}

void Scene::Update(const float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::FixedUpdate(const float fixedTimeStep)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(fixedTimeStep);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

