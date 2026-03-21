#include "Subject.h"
#include <algorithm>

namespace dae
{
    Subject::~Subject()
    {
        for (auto* observer : m_observers)
            observer->OnSubjectDestroyed();
        m_observers.clear();
    }

    void Subject::AddObserver(Observer* observer)
    {
        m_observers.push_back(observer);
    }

    void Subject::RemoveObserver(Observer* observer)
    {
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
    }

    void Subject::NotifyObservers(EventId event)
    {
        for (auto* observer : m_observers)
            observer->Notify(event);
    }
}