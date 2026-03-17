#pragma once
#include "Observer.h"
#include <vector>

namespace dae
{
    class Subject
    {
    public:
        virtual ~Subject();
        void AddObserver(Observer* observer);
        void RemoveObserver(Observer* observer);

    protected:
        void NotifyObservers(EventId event);

    private:
        std::vector<Observer*> m_observers;
    };
}