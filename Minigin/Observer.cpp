#include "Observer.h"
#include "Subject.h"

namespace dae
{
    Observer::Observer(Subject* subject) : m_subject(subject)
    {
        m_subject->AddObserver(this);
    }

    Observer::~Observer()
    {
        if (m_subject)
            m_subject->RemoveObserver(this);
    }
}