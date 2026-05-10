#include "PlayerHitObserver.h"
#include "HitboxComponent.h"
#include "CharacterStateComponent.h"
#include "HurtState.h"

namespace dae
{
    PlayerHitObserver::PlayerHitObserver(GameObject* owner, HitboxComponent* hitbox, CharacterStateComponent* stateComp)
        : BaseComponent(owner), m_pHitbox(hitbox), m_pStateComp(stateComp)
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
            m_pStateComp->SetState(std::make_unique<HurtState>());
    }

    void PlayerHitObserver::OnSubjectDestroyed()
    {
        m_pHitbox = nullptr;
    }
}