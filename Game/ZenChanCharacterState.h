#pragma once
#include <memory>

namespace dae
{
    class ZenChanStateController;

    class ZenChanCharacterState
    {
    public:
        virtual ~ZenChanCharacterState() = default;
        ZenChanCharacterState(const ZenChanCharacterState&) = delete;
        ZenChanCharacterState& operator=(const ZenChanCharacterState&) = delete;
        ZenChanCharacterState(ZenChanCharacterState&&) = delete;
        ZenChanCharacterState& operator=(ZenChanCharacterState&&) = delete;

        virtual void OnEnter(ZenChanStateController* controller) = 0;
        virtual std::unique_ptr<ZenChanCharacterState> Update(ZenChanStateController* controller, float deltaTime) = 0;
        virtual void OnExit(ZenChanStateController* controller) = 0;

    protected:
        ZenChanCharacterState() = default;
    };
}