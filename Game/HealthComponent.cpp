#include "HealthComponent.h"
#include "EventId.h"

namespace dae
{
    HealthComponent::HealthComponent(GameObject* owner, int lives)
        : BaseComponent(owner), m_lives(lives)
    {
    }

    void HealthComponent::LoseLife()
    {
        if (m_lives <= 0) return;
        --m_lives;
        NotifyObservers(make_sdbm_hash("PlayerDied"));
    }
}