#pragma once
#include "PlayerCharacterState.h"

namespace dae
{
    class RespawnState final : public PlayerCharacterState
    {
    public:
        explicit RespawnState(float duration = 0.5f, float invincibilityDuration = 2.f);
        ~RespawnState() override = default;

        void OnEnter(PlayerStateController* controller) override;
        std::unique_ptr<PlayerCharacterState> Update(PlayerStateController* controller, float deltaTime) override;
        void OnExit(PlayerStateController* controller) override;
        bool BlocksMovement() const override { return true; }

    private:
        float m_duration;
        float m_invincibilityDuration;
        float m_timer{ 0.f };
    };
}