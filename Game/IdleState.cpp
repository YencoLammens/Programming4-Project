#include "IdleState.h"
#include "GameObject.h"

namespace dae
{
    void IdleState::OnEnter(GameObject*)
    {
    }

    std::unique_ptr<CharacterState> IdleState::HandleInput(GameObject*)
    {
        return nullptr;
    }

    void IdleState::Update(GameObject*, float)
    {
    }

    void IdleState::OnExit(GameObject*)
    {
    }
}