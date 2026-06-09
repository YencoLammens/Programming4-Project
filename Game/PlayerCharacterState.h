#pragma once
#include <memory>

namespace dae
{
    class PlayerStateController;

    class PlayerCharacterState
    {
    public:
        virtual ~PlayerCharacterState() = default;
        PlayerCharacterState(const PlayerCharacterState&) = delete;
        PlayerCharacterState& operator=(const PlayerCharacterState&) = delete;
        PlayerCharacterState(PlayerCharacterState&&) = delete;
        PlayerCharacterState& operator=(PlayerCharacterState&&) = delete;

        virtual void OnEnter(PlayerStateController* controller) = 0;
        virtual std::unique_ptr<PlayerCharacterState> Update(PlayerStateController* controller, float deltaTime) = 0;
        virtual void OnExit(PlayerStateController* controller) = 0;

    protected:
        PlayerCharacterState() = default;
    };
}