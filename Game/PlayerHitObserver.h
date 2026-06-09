#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "EventId.h"

namespace dae
{
    class HitboxComponent;
    class PlayerStateController;

    class PlayerHitObserver final : public BaseComponent, public Observer
    {
    public:
        PlayerHitObserver(GameObject* owner, HitboxComponent* hitbox, PlayerStateController* stateComp);
        ~PlayerHitObserver() override;
        PlayerHitObserver(const PlayerHitObserver&) = delete;
        PlayerHitObserver& operator=(const PlayerHitObserver&) = delete;
        PlayerHitObserver(PlayerHitObserver&&) = delete;
        PlayerHitObserver& operator=(PlayerHitObserver&&) = delete;

        void Update(const float) override {}
        void FixedUpdate(const float) override {}

        void Notify(EventId id) override;
        void OnSubjectDestroyed() override;

    private:
        HitboxComponent* m_pHitbox;
        PlayerStateController* m_stateController;
    };
}