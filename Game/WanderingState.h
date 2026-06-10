#pragma once
#include "EnemyCharacterState.h"

namespace dae
{
    class WanderingState final : public EnemyCharacterState
    {
    public:
        explicit WanderingState(float speed = 80.f);
        ~WanderingState() override = default;

        void OnEnter(IEnemyStateController* controller) override;
        std::unique_ptr<EnemyCharacterState> Update(IEnemyStateController* controller, float deltaTime) override;
        void OnExit(IEnemyStateController* controller) override;

    private:
        float m_speed;
        float m_direction{ 1.f };
        float m_jumpTimer{ 0.f };
        float m_jumpInterval{ 0.f };

        static constexpr float k_wallMargin = 4.f;
    };
}