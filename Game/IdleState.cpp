#include "IdleState.h"
#include "GameObject.h"

namespace dae
{
    void IdleState::OnEnter(GameObject*)
    {
    }

    std::unique_ptr<CharacterState> IdleState::HandleInput(GameObject*, float)
    {
        return nullptr;
    }

    void IdleState::OnExit(GameObject*)
    {
    }
}