#include "IdleState.h"
#include "HurtState.h"
#include "CharacterStateComponent.h"
#include "GameObject.h"

namespace dae
{
    void IdleState::OnEnter(GameObject*)
    {
        m_wasHit = false;
    }

    std::unique_ptr<CharacterState> IdleState::HandleInput(GameObject*)
    {
        if (m_wasHit)
            return std::make_unique<HurtState>();
        return nullptr;
    }

    void IdleState::Update(GameObject*, float)
    {
    }

    void IdleState::OnExit(GameObject*)
    {
    }

    void IdleState::NotifyHit()
    {
        m_wasHit = true;
    }
}