#pragma once
#include "CharacterState.h"

namespace dae
{
    class IdleState final : public CharacterState
    {
    public:
        IdleState() = default;
        ~IdleState() override = default;

        void OnEnter(GameObject* owner) override;
        std::unique_ptr<CharacterState> HandleInput(GameObject* owner) override;
        void Update(GameObject* owner, float deltaTime) override;
        void OnExit(GameObject* owner) override;
        void NotifyHit();

    private:
        bool m_wasHit{ false };
    };
}