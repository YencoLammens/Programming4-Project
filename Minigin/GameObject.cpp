#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"

dae::GameObject::GameObject() 
    :m_worldPosition(0.0f, 0.0f, 0.0f), m_localPosition(0.0f, 0.0f, 0.0f), m_transform(std::make_unique<TransformComponent>(this))
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
    for (auto& component : m_componentsArr)
    {
        component->Update(deltaTime);
    }
}

void dae::GameObject::FixedUpdate(float fixedTimeStep)
{
    for (auto& component : m_componentsArr)
    {
        component->FixedUpdate(fixedTimeStep);
    }
}

void dae::GameObject::Render() const
{
    for (const auto& component : m_componentsArr)
    {
        if (auto* renderable = dynamic_cast<IRenderable*>(component.get()))
        {
            renderable->Render();
        }
    }
}

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> component)
{
	m_componentsArr.push_back(std::move(component));
}

void dae::GameObject::RemoveComponent(BaseComponent* toBeDeletedComponent)
{
    for (auto& component : m_componentsArr)
    {
        if (component.get() == toBeDeletedComponent)
        {
            component->MarkForDeletion();
            m_mustAComponentBeDeleted = true;

            break;
        }
    }

}

dae::TransformComponent* dae::GameObject::GetTransform()
{
    return m_transform.get();
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent == this || m_parent == parent)
        return;
    if (parent == nullptr)
        m_transform->SetLocalPosition(m_transform->GetWorldPosition());
    else
    {
        if (keepWorldPosition)
            m_transform->SetLocalPosition(m_transform->GetWorldPosition() - parent->GetTransform()->GetWorldPosition());
        m_transform->SetPositionDirty();
    }
    if (m_parent) m_parent->RemoveChild(this);
    m_parent = parent;
    if (m_parent) m_parent->AddChild(this);
}

dae::GameObject* dae::GameObject::GetParent()
{
    if (m_parent)
    {
        return m_parent;
    }
    return nullptr;
}

void dae::GameObject::AddChild(GameObject* newChild)
{
    m_childrenArr.push_back(newChild);
}

void dae::GameObject::RemoveChild(GameObject* orphanedChild)
{
    for (unsigned int idx{ 0 }; idx < m_childrenArr.size(); ++idx)
    {
        if (m_childrenArr[idx] == orphanedChild)
        {
            m_childrenArr[idx]->SetParent(nullptr, true);
            m_childrenArr.erase(m_childrenArr.begin() + idx);
            return;
        }
    }
}

bool dae::GameObject::IsChild(GameObject* possibleChild) const
{
    for (unsigned int idx{ 0 }; idx < m_childrenArr.size(); ++idx)
    {
        if (m_childrenArr[idx] == possibleChild)
        {
            return true;
        }
    }
    return false;
}

std::vector<dae::GameObject*> dae::GameObject::GetChildren()
{
    return m_childrenArr;
}

void dae::GameObject::MarkForDeletion()
{
    m_toBeDeleted = true;
    SceneManager::GetInstance().SetDeletionPending();

    for (auto& child : m_childrenArr)
    {
        this->RemoveChild(child);
    }

    for (auto& component : m_componentsArr)
    {
        component->MarkForDeletion();
    }
}

void dae::GameObject::RemoveFlaggedComponents()
{
    if (!m_mustAComponentBeDeleted) return;

    SceneManager::GetInstance().SetDeletionPending();

    for (unsigned int idx{ 0 }; idx < m_componentsArr.size(); ++idx)
    {
        if (m_componentsArr[idx]->IsMarkedForDeletion())
        {
            m_componentsArr.erase(m_componentsArr.begin() + idx);
            --idx;
        }
    }
    m_mustAComponentBeDeleted = false;
}
