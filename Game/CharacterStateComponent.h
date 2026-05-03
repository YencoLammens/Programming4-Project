#pragma once
#include <memory>
#include "BaseComponent.h"
#include "CharacterState.h"

namespace dae
{
    class CharacterStateComponent final : public BaseComponent
    {
    public:
        CharacterStateComponent(GameObject* owner, std::unique_ptr<CharacterState> initialState);
        ~CharacterStateComponent() override = default;
        CharacterStateComponent(const CharacterStateComponent&) = delete;
        CharacterStateComponent& operator=(const CharacterStateComponent&) = delete;
        CharacterStateComponent(CharacterStateComponent&&) = delete;
        CharacterStateComponent& operator=(CharacterStateComponent&&) = delete;

        void Update(const float deltaTime) override;
        void FixedUpdate(const float) override {}

        void SetState(std::unique_ptr<CharacterState> newState);

    private:
        std::unique_ptr<CharacterState> m_currentState;
    };
}