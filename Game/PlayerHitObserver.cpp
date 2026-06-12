#include "PlayerHitObserver.h"
#include "HitboxComponent.h"
#include "PlayerStateController.h"
#include "CollisionLayer.h"
#include "ServiceLocator.h"

namespace dae
{
    PlayerHitObserver::PlayerHitObserver(GameObject* owner, HitboxComponent* hitbox, PlayerStateController* stateController)
        : BaseComponent(owner), m_pHitbox(hitbox), m_stateController(stateController)
    {
        m_pHitbox->AddObserver(this);
    }

    PlayerHitObserver::~PlayerHitObserver()
    {
        if (m_pHitbox)
            m_pHitbox->RemoveObserver(this);
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
				ServiceLocator::GetSoundSystem().Play(5, 0.3f);
            }
        }
    }

    void PlayerHitObserver::OnSubjectDestroyed()
    {
        m_pHitbox = nullptr;
    }
}