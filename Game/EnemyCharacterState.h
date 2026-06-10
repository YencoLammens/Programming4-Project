#pragma once
#include <memory>

namespace dae
{
    class IEnemyStateController;

    class EnemyCharacterState
    {
    public:
        virtual ~EnemyCharacterState() = default;
        EnemyCharacterState(const EnemyCharacterState&) = delete;
        EnemyCharacterState& operator=(const EnemyCharacterState&) = delete;
        EnemyCharacterState(EnemyCharacterState&&) = delete;
        EnemyCharacterState& operator=(EnemyCharacterState&&) = delete;

        virtual void OnEnter(IEnemyStateController* controller) = 0;
        virtual std::unique_ptr<EnemyCharacterState> Update(IEnemyStateController* controller, float deltaTime) = 0;
        virtual void OnExit(IEnemyStateController* controller) = 0;

    protected:
        EnemyCharacterState() = default;
    };
}