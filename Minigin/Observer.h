#pragma once
#include "EventId.h"

namespace dae
{
    class Subject;
    class Observer
    {
    public:
        Observer(Subject* subject);

        virtual ~Observer();

        Observer(const Observer&) = delete;
        Observer& operator=(const Observer&) = delete;
        Observer(Observer&&) = delete;
        Observer& operator=(Observer&&) = delete;

        virtual void Notify(EventId event) = 0;
        void OnSubjectDestroyed() { m_subject = nullptr; }

    private:
        Subject* m_subject;
    };
}