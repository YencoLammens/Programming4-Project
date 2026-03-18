#include "ScoreComponent.h"
#include "EventId.h"

namespace dae
{
    ScoreComponent::ScoreComponent(GameObject* owner)
        : BaseComponent(owner)
    {
    }

    void ScoreComponent::AddPoints(int points)
    {
        m_score += points;
        NotifyObservers(make_sdbm_hash("PointsGained"));
    }
}