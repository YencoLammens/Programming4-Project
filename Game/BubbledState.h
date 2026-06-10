#pragma once
#include "EnemyCharacterState.h"

namespace dae
{
    class BubbledState final : public EnemyCharacterState
    {
    public:
        explicit BubbledState(float duration = 5.f);
        ~BubbledState() override = default;

        void OnEnter(IEnemyStateController* controller) override;
        std::unique_ptr<EnemyCharacterState> Update(IEnemyStateController* controller, float deltaTime) override;
        void OnExit(IEnemyStateController* controller) override;

    private:
        float m_duration;
        float m_timer{ 0.f };

        static constexpr float k_floatSpeed = 40.f;
    };
}