#include "CollisionManager.h"
#include "HitboxComponent.h"
#include <algorithm>

namespace dae
{
    void CollisionManager::Register(HitboxComponent* hitbox)
    {
        m_hitboxes.push_back(hitbox);
    }

    void CollisionManager::Unregister(HitboxComponent* hitbox)
    {
        m_hitboxes.erase(std::remove(m_hitboxes.begin(), m_hitboxes.end(), hitbox), m_hitboxes.end());

        for (auto it = m_activeOverlaps.begin(); it != m_activeOverlaps.end(); )
        {
            if (it->first == hitbox || it->second == hitbox)
            {
                it = m_activeOverlaps.erase(it);
            }
                
            else
            {
                ++it;
            }
        }
    }

    void CollisionManager::Update()
    {
        std::set<std::pair<HitboxComponent*, HitboxComponent*>> currentOverlaps;

        for (size_t i = 0; i < m_hitboxes.size(); ++i)
        {
            for (size_t j = i + 1; j < m_hitboxes.size(); ++j)
            {
                HitboxComponent* a = m_hitboxes[i];
                HitboxComponent* b = m_hitboxes[j];
                if (a->Overlaps(*b))
                    currentOverlaps.insert({ a, b });
            }
        }

        for (const auto& pair : currentOverlaps)
        {
            if (m_activeOverlaps.find(pair) == m_activeOverlaps.end())
            {
                pair.first->BeginOverlap(pair.second);
                pair.second->BeginOverlap(pair.first);
            }
        }

        for (const auto& pair : m_activeOverlaps)
        {
            if (currentOverlaps.find(pair) == currentOverlaps.end())
            {
                pair.first->EndOverlap(pair.second);
                pair.second->EndOverlap(pair.first);
            }
        }

        m_activeOverlaps = currentOverlaps;
    }
}