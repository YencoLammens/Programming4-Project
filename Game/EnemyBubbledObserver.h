#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
    class HitboxComponent;
    class IEnemyStateController;

    class EnemyBubbledObserver final : public BaseComponent, public Observer
    {
    public:
        EnemyBubbledObserver(GameObject* owner, HitboxComponent* hitbox, IEnemyStateController* stateController);
        ~EnemyBubbledObserver() override;
        EnemyBubbledObserver(const EnemyBubbledObserver&) = delete;
        EnemyBubbledObserver& operator=(const EnemyBubbledObserver&) = delete;
        EnemyBubbledObserver(EnemyBubbledObserver&&) = delete;
        EnemyBubbledObserver& operator=(EnemyBubbledObserver&&) = delete;

        void Update(float) override {}
        void FixedUpdate(float) override {}
        void Notify(EventId event) override;
        void OnSubjectDestroyed() override { m_pHitbox = nullptr; }

    private:
        HitboxComponent* m_pHitbox;
        IEnemyStateController* m_pStateController;
    };
}