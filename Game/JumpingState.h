#pragma once
#include "PlayerCharacterState.h"

namespace dae
{
    class JumpingState final : public PlayerCharacterState
    {
    public:
        explicit JumpingState(float duration = 0.5f);
        ~JumpingState() override = default;

        void OnEnter(PlayerStateController* controller) override;
        std::unique_ptr<PlayerCharacterState> Update(PlayerStateController* controller, float deltaTime) override;
        void OnExit(PlayerStateController* controller) override;

    private:
        float m_timer{ 0.f };
        float m_duration;
    };
}