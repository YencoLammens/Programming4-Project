#include "ScoreDisplay.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include "Subject.h"
#include "GameObject.h"
#include "EventId.h"

namespace dae
{
    ScoreDisplay::ScoreDisplay(GameObject* owner, Subject* subject, ScoreComponent* scoreComponent)
        : BaseComponent(owner), m_scoreComponent(scoreComponent), m_subject(subject)
    {
        m_textComponent = owner->GetComponent<TextComponent>();
        m_subject->AddObserver(this);
    }

    ScoreDisplay::~ScoreDisplay()
    {
        if (m_subject)
            m_subject->RemoveObserver(this);
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