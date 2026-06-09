#pragma once
#include "ZenChanCharacterState.h"

namespace dae
{
    class PoppedState final : public ZenChanCharacterState
    {
    public:
        explicit PoppedState(float duration = 0.6f);
        ~PoppedState() override = default;

        void OnEnter(ZenChanStateController* controller) override;
        std::unique_ptr<ZenChanCharacterState> Update(ZenChanStateController* controller, float deltaTime) override;
        void OnExit(ZenChanStateController* controller) override;

    private:
        float m_duration;
        float m_timer{ 0.f };

        static constexpr float k_flySpeed = 200.f;
    };
}