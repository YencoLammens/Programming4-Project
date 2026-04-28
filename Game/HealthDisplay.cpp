#include "HealthDisplay.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "Subject.h"
#include "GameObject.h"
#include "EventId.h"

namespace dae
{
    HealthDisplay::HealthDisplay(GameObject* owner, Subject* subject, HealthComponent* healthComponent)
        : BaseComponent(owner), m_healthComponent(healthComponent), m_subject(subject)
    {
        m_textComponent = owner->GetComponent<TextComponent>();
        m_subject->AddObserver(this);
    }

    HealthDisplay::~HealthDisplay()
    {
        if (m_subject)
            m_subject->RemoveObserver(this);
    }

    void HealthDisplay::Notify(EventId event)
    {
        if (event == make_sdbm_hash("PlayerDied"))
        {
            if (m_textComponent && m_healthComponent)
                m_textComponent->SetText("# lives: " + std::to_string(m_healthComponent->GetLives()));
        }
    }
}