#pragma once
#include "CharacterState.h"

namespace dae
{
    class DeadState final : public CharacterState
    {
    public:
        explicit DeadState(float duration = 1.f);
        ~DeadState() override = default;

        void OnEnter(GameObject* owner) override;
        std::unique_ptr<CharacterState> HandleInput(GameObject* owner) override;
        void Update(GameObject* owner, float deltaTime) override;
        void OnExit(GameObject* owner) override;

    private:
        float m_duration;
        float m_timer;
    };
}