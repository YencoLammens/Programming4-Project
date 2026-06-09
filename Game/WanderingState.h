#pragma once
#include "ZenChanCharacterState.h"

namespace dae
{
    class WanderingState final : public ZenChanCharacterState
    {
    public:
        explicit WanderingState(float speed = 80.f);
        ~WanderingState() override = default;

        void OnEnter(ZenChanStateController* controller) override;
        std::unique_ptr<ZenChanCharacterState> Update(ZenChanStateController* controller, float deltaTime) override;
        void OnExit(ZenChanStateController* controller) override;

    private:
        float m_speed;
        float m_direction{ 1.f };

        static constexpr float k_wallMargin = 4.f;
    };
}