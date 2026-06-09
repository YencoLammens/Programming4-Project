#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "FacingComponent.h"
#include "HealthComponent.h"
#include "BubblePoolComponent.h"
#include "GameObject.h"

namespace dae
{
    PlayerStateController::PlayerStateController(GameObject* owner, std::unique_ptr<PlayerCharacterState> initialState, BubblePoolComponent* bubblePool)
        : BaseComponent(owner), m_currentState(std::move(initialState)), m_animation(owner->GetComponent<AnimationComponent>()), m_physics(owner->GetComponent<PhysicsComponent>()), m_facing(owner->GetComponent<FacingComponent>()), m_health(owner->GetComponent<HealthComponent>()), m_bubblePool(bubblePool)
    {
        if (m_currentState)
            m_currentState->OnEnter(this);
    }

    void PlayerStateController::Update(float deltaTime)
    {
        if (!m_currentState) return;
        auto newState = m_currentState->Update(this, deltaTime);
        if (newState)
            SetState(std::move(newState));
        m_jumpRequested = false;
        m_shootRequested = false;
        m_hurtRequested = false;
        m_moveRequested = false;
    }

    void PlayerStateController::OnJump() { m_jumpRequested = true; }
    void PlayerStateController::OnShoot() { m_shootRequested = true; }
    void PlayerStateController::OnHurt() { m_hurtRequested = true; }
    void PlayerStateController::OnMove() { m_moveRequested = true; }

    bool PlayerStateController::IsMoving() const
    {
        return m_moveRequested;
    }

    void PlayerStateController::SetState(std::unique_ptr<PlayerCharacterState> newState)
    {
        if (m_currentState)
            m_currentState->OnExit(this);
        m_currentState = std::move(newState);
        if (m_currentState)
            m_currentState->OnEnter(this);
    }
}