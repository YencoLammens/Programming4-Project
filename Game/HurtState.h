#pragma once
#include "CharacterState.h"

namespace dae
{
    class HurtState final : public CharacterState
    {
    public:
        explicit HurtState(float duration = 2.f);
        ~HurtState() override = default;

        void OnEnter(GameObject* owner) override;
        std::unique_ptr<CharacterState> HandleInput(GameObject* owner) override;
        void Update(GameObject* owner, float deltaTime) override;
        void OnExit(GameObject* owner) override;

    private:
        float m_duration;
        float m_timer{ 0.f };
    };
}