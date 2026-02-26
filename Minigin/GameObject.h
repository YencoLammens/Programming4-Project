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
		~GameObject(); //Default in cpp, not here cause of the unique_ptr member
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(const float deltaTime);
		void FixedUpdate(const float fixedTimeStep);
		void Render() const;

		//void AddComponent(std::unique_ptr<BaseComponent> component);
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<BaseComponent, T>::value, "T must derive from BaseComponent");

			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			T* componentPtr = component.get();
			m_componentsArr.emplace_back(std::move(component));
			return componentPtr;
		}
		void RemoveComponent(BaseComponent* baseComponent);

		template <typename T>
		bool HasComponent() const 
		{
			for (const auto& component : m_componentsArr)
			{
				if (dynamic_cast<T*>(component.get()))
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

		TransformComponent* GetTransform() const;

		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent();

		std::vector<GameObject*> GetChildren();

		void MarkForDeletion();
		bool IsMarkedForDeletion() const { return m_toBeDeleted; }
		void RemoveFlaggedComponents();

	private:
		bool IsChild(GameObject* possibleChild) const;
		void AddChild(GameObject* newChild);
		void RemoveChild(GameObject* orphanedChild);
		std::vector<std::unique_ptr<BaseComponent>> m_componentsArr;
		std::vector<GameObject*> m_childrenArr;
		GameObject* m_parent{ nullptr };

		std::unique_ptr<TransformComponent> m_transform;

		bool m_mustAComponentBeDeleted = false;
		bool m_toBeDeleted = false;

		
	};
}
