#pragma once
#include "EnemyCharacterState.h"

namespace dae
{
    class FoodPoolComponent;

    class PoppedState final : public EnemyCharacterState
    {
    public:
        explicit PoppedState(FoodPoolComponent* foodPool, float riseDuration = 0.4f);
        ~PoppedState() override = default;

        void OnEnter(IEnemyStateController* controller) override;
        std::unique_ptr<EnemyCharacterState> Update(IEnemyStateController* controller, float deltaTime) override;
        void OnExit(IEnemyStateController* controller) override;

    private:
        FoodPoolComponent* m_pFoodPool;
        float m_riseDuration;
        float m_riseTimer{ 0.f };
        float m_fallTimer{ 0.f };
        float m_horizontalDir{ 1.f };
        bool m_falling{ false };

        static constexpr float k_riseSpeed{ 200.f };
        static constexpr float k_horizontalSpeed{ 80.f };
        static constexpr float k_fallGrace{ 0.1f };
        static constexpr float k_maxFallTime{ 5.f };
    };
}