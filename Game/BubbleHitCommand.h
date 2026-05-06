#pragma once
#include "Command.h"
#include "CharacterStateComponent.h"

namespace dae
{
    class BubbleHitCommand final : public GameObjectCommand
    {
    public:
        BubbleHitCommand(GameObject* gameObject, CharacterStateComponent* stateComponent);
        ~BubbleHitCommand() override = default;
        BubbleHitCommand(const BubbleHitCommand&) = delete;
        BubbleHitCommand& operator=(const BubbleHitCommand&) = delete;
        BubbleHitCommand(BubbleHitCommand&&) = delete;
        BubbleHitCommand& operator=(BubbleHitCommand&&) = delete;

        void Execute(float deltaTime) override;

    private:
        CharacterStateComponent* m_stateComponent;
    };
}