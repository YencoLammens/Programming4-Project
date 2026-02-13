#pragma once
#include <string>
#include <memory>
#include <glm/glm.hpp>

#include "BaseComponent.h"


namespace dae
{
	class TransformComponent;
	class GameObject final
	{
	public:

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float fixedTimeStep);
		virtual void Render() const;

		void AddComponent(std::unique_ptr<BaseComponent> component);
		void RemoveComponent(BaseComponent* baseComponent);

		//Templates
		template <typename T>
		T HasComponentBeenAdded() const
		{
			for (const auto& component : m_componentsArr)
			{
				if (dynamic_cast<T>(component))
				{
					return true;
				}
			}
			return false;
		}

		//Tries to find the component type inside of the component vector by attempting to dynamic cast it to the given type, if it finds one, that one gets returned (the first one)
		template <typename T>
		T* GetComponent() const
		{
			for (const auto& component : m_componentsArr)
			{
				if (auto castedComponent = dynamic_cast<T*>(component.get()))
				{
					return castedComponent;
				}
			}
			return nullptr;
		}

		TransformComponent* GetTransform();

		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent();

		void AddChild(GameObject* newChild);
		void RemoveChild(GameObject* orphanedChild);
		bool IsChild(GameObject* possibleChild) const;

		

		std::vector<GameObject*> GetChildren();

		void MarkForDeletion();
		bool IsMarkedForDeletion() const { return m_toBeDeleted; }
		void RemoveFlaggedComponents();

	private:

		std::vector<std::unique_ptr<BaseComponent>> m_componentsArr;
		std::vector<GameObject*> m_childrenArr;
		GameObject* m_parent{ nullptr };

		glm::vec3 m_worldPosition{};
		glm::vec3 m_localPosition{};
		std::unique_ptr<TransformComponent> m_transform;

		bool m_mustAComponentBeDeleted = false;
		bool m_toBeDeleted = false;

		
	};
}
