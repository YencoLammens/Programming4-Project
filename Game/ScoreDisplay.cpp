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
            {
                const auto s = std::to_string(m_scoreComponent->GetScore());
                m_textComponent->SetText(std::string(s.size() < 6u ? 6u - s.size() : 0u, '0') + s);
            }
        }
    }
}