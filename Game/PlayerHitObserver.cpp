#include "PlayerHitObserver.h"
#include "HitboxComponent.h"
#include "PlayerStateController.h"
#include "HealthComponent.h"
#include "CollisionLayer.h"
#include "ServiceLocator.h"
#include "GameState.h"

namespace dae
{
    PlayerHitObserver::PlayerHitObserver(GameObject* owner, HitboxComponent* hitbox, PlayerStateController* stateController)
        : BaseComponent(owner), m_pHitbox(hitbox), m_pHealth(stateController->GetHealthComponent()), m_stateController(stateController)
    {
        m_pHitbox->AddObserver(this);
        if (m_pHealth)
            m_pHealth->AddObserver(this);
    }

    PlayerHitObserver::~PlayerHitObserver()
    {
        if (m_pHitbox)
            m_pHitbox->RemoveObserver(this);
        if (m_pHealth)
            m_pHealth->RemoveObserver(this);
    }

    void PlayerHitObserver::Notify(EventId id)
    {
        if (id == make_sdbm_hash("OnOverlapBegin"))
        {
            if (m_stateController->IsInvincible())
                return;
            auto* partner = m_pHitbox->GetOverlapPartner();
            if (partner && (partner->GetLayer() == CollisionLayer::Enemy || partner->GetLayer() == CollisionLayer::Boulder))
            {
                m_stateController->OnHurt();
				ServiceLocator::GetSoundSystem().Play(5, 0.2f);
            }
        }
        if (id == dae::make_sdbm_hash("GameOver"))
        {
            if (dae::GameState::onGameOver)
                std::exchange(dae::GameState::onGameOver, {})(); // clears the callback before calling it
        }

    }

    void PlayerHitObserver::OnSubjectDestroyed()
    {
        m_pHitbox = nullptr;
        m_pHealth = nullptr;
    }
}