#pragma once
#include "PlayerCharacterState.h"

namespace dae
{
    class IdleState final : public PlayerCharacterState
    {
    public:
        IdleState() = default;
        ~IdleState() override = default;

        void OnEnter(PlayerStateController* controller) override;
        std::unique_ptr<PlayerCharacterState> Update(PlayerStateController* controller, float deltaTime) override;
        void OnExit(PlayerStateController* controller) override;
    };
}