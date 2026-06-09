#pragma once
#include "ZenChanCharacterState.h"

namespace dae
{
    class BubbledState final : public ZenChanCharacterState
    {
    public:
        explicit BubbledState(float duration = 5.f);
        ~BubbledState() override = default;

        void OnEnter(ZenChanStateController* controller) override;
        std::unique_ptr<ZenChanCharacterState> Update(ZenChanStateController* controller, float deltaTime) override;
        void OnExit(ZenChanStateController* controller) override;

    private:
        float m_duration;
        float m_timer{ 0.f };

        static constexpr float k_floatSpeed = 40.f;
    };
}