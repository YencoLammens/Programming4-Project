#pragma once
#include "CharacterState.h"

namespace dae
{
    class BubbledState final : public CharacterState
    {
    public:
        explicit BubbledState(float duration = 5.f);
        ~BubbledState() override = default;

        void OnEnter(GameObject* owner) override;
        std::unique_ptr<CharacterState> HandleInput(GameObject* owner, float deltaTime) override;
        void OnExit(GameObject* owner) override;

    private:
        float m_duration;
        float m_timer;

        static constexpr float k_floatSpeed = 40.f;
    };
}