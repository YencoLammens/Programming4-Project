#pragma once
#include "EventId.h"

namespace dae
{
    class Observer
    {
    public:
        virtual ~Observer() = default;
        virtual void Notify(EventId event) = 0;
        virtual void OnSubjectDestroyed() {}

        Observer(const Observer&) = delete;
        Observer& operator=(const Observer&) = delete;
        Observer(Observer&&) = delete;
        Observer& operator=(Observer&&) = delete;

    protected:
        Observer() = default;
    };
}