#pragma once
#include "PlayerCharacterState.h"

namespace dae
{
    class HurtState final : public PlayerCharacterState
    {
    public:
        explicit HurtState(float duration = 2.f);
        ~HurtState() override = default;

        void OnEnter(PlayerStateController* controller) override;
        std::unique_ptr<PlayerCharacterState> Update(PlayerStateController* controller, float deltaTime) override;
        void OnExit(PlayerStateController* controller) override;

    private:
        float m_duration;
        float m_timer{ 0.f };
    };
}