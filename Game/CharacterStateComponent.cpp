#include "CharacterStateComponent.h"
#include "GameObject.h"

namespace dae
{
    CharacterStateComponent::CharacterStateComponent(GameObject* owner, std::unique_ptr<CharacterState> initialState)
        : BaseComponent(owner), m_currentState(std::move(initialState))
    {
        if (m_currentState)
            m_currentState->OnEnter(GetOwner());
    }

    void CharacterStateComponent::Update(const float deltaTime)
    {
        if (!m_currentState) return;

        auto newState = m_currentState->HandleInput(GetOwner(), deltaTime);
        if (newState)
            SetState(std::move(newState));
    }

    void CharacterStateComponent::SetState(std::unique_ptr<CharacterState> newState)
    {
        if (m_currentState)
            m_currentState->OnExit(GetOwner());
        m_currentState = std::move(newState);
        if (m_currentState)
            m_currentState->OnEnter(GetOwner());
    }
}