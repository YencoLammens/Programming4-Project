#include "LevelManagerComponent.h"
#include "GameObject.h"
#include <algorithm>

namespace dae
{
    LevelManagerComponent::LevelManagerComponent(GameObject* owner)
        : BaseComponent(owner)
    {
    }

    void LevelManagerComponent::RegisterEnemy(GameObject* enemy)
    {
        m_enemies.push_back(enemy);
    }

    void LevelManagerComponent::SetOnLevelComplete(std::function<void()> callback)
    {
        m_onLevelComplete = std::move(callback);
    }

    void LevelManagerComponent::Update(float deltaTime)
    {
        if (m_levelComplete)
        {
            m_transitionTimer -= deltaTime;
            if (m_transitionTimer <= 0.f)
            {
                m_levelComplete = false;
                m_enemies.clear();
                if (m_onLevelComplete)
                    m_onLevelComplete();
            }
            return;
        }

        if (m_enemies.empty()) return;

        m_enemies.erase( std::remove_if(m_enemies.begin(), m_enemies.end(), [](const GameObject* e) { return e->IsMarkedForDeletion(); }),m_enemies.end());
        if (m_enemies.empty())
        {
            m_levelComplete = true;
            m_transitionTimer = s_transitionDelay;
        }
    }
}