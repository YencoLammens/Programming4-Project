#pragma once
#include "CharacterState.h"

namespace dae
{
    class WanderingState final : public CharacterState
    {
    public:
        explicit WanderingState(float speed = 80.f);
        ~WanderingState() override = default;

        void OnEnter(GameObject* owner) override;
        std::unique_ptr<CharacterState> HandleInput(GameObject* owner, float deltaTime) override;
        void OnExit(GameObject* owner) override;

    private:
        float m_speed;
        float m_direction;
    };
}