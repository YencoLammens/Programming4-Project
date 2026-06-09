#pragma once
#include "PlayerCharacterState.h"

namespace dae
{
    class WalkingState final : public PlayerCharacterState
    {
    public:
        WalkingState() = default;
        ~WalkingState() override = default;

        void OnEnter(PlayerStateController* controller) override;
        std::unique_ptr<PlayerCharacterState> Update(PlayerStateController* controller, float deltaTime) override;
        void OnExit(PlayerStateController* controller) override;
    };
}