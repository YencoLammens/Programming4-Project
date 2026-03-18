#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "EventId.h"

namespace dae
{
    ScoreDisplay::ScoreDisplay(GameObject* owner, Subject* subject, ScoreComponent* scoreComponent)
        : BaseComponent(owner), Observer(subject), m_scoreComponent(scoreComponent)
    {
        m_textComponent = owner->GetComponent<TextComponent>();
    }

    void ScoreDisplay::Notify(EventId event)
    {
        if (event == make_sdbm_hash("PointsGained"))
        {
            if (m_textComponent && m_scoreComponent)
                m_textComponent->SetText("Score: " + std::to_string(m_scoreComponent->GetScore()));
        }
    }
}