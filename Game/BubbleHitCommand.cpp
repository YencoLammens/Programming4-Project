#include "BubbleHitCommand.h"
#include "BubbledState.h"

namespace dae
{
    BubbleHitCommand::BubbleHitCommand(GameObject* gameObject, CharacterStateComponent* stateComponent)
        : GameObjectCommand(gameObject), m_stateComponent(stateComponent)
    {
    }

    void BubbleHitCommand::Execute(float)
    {
        m_stateComponent->SetState(std::make_unique<BubbledState>());
    }
}