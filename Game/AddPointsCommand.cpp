#include "AddPointsCommand.h"

namespace dae
{
    AddPointsCommand::AddPointsCommand(GameObject* gameObject, ScoreComponent* scoreComponent, int points)
        : GameObjectCommand(gameObject), m_scoreComponent(scoreComponent), m_points(points)
    {
    }

    void AddPointsCommand::Execute(float)
    {
        m_scoreComponent->AddPoints(m_points);
    }
}