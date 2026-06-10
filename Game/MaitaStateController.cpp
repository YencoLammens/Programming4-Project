#include "MaitaStateController.h"
#include "MaitaShootComponent.h"
#include "HitboxComponent.h"
#include "PhysicsComponent.h"
#include "FacingComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "FoodPoolComponent.h"
#include "BubbledState.h"
#include "PoppedState.h"
#include "GameObject.h"

namespace dae
{
    MaitaStateController::MaitaStateController(GameObject* owner, std::unique_ptr<EnemyCharacterState> initialState, FoodPoolComponent* foodPool, MaitaShootComponent* shoot)
        : BaseComponent(owner), m_currentState(std::move(initialState)), m_pFoodPool(foodPool), m_pShoot(shoot), m_hitbox(owner->GetComponent<HitboxComponent>()), m_physics(owner->GetComponent<PhysicsComponent>()), m_facing(owner->GetComponent<FacingComponent>()), m_render(owner->GetComponent<RenderComponent>()), m_animation(owner->GetComponent<AnimationComponent>())
    {
        if (m_currentState)
            m_currentState->OnEnter(this);
    }

    void MaitaStateController::Update(float deltaTime)
    {
        if (!m_currentState) return;
        auto newState = m_currentState->Update(this, deltaTime);
        if (newState)
            SetState(std::move(newState));
    }

    void MaitaStateController::OnBubbled()
    {
        if (m_pShoot) m_pShoot->SetEnabled(false);
        SetState(std::make_unique<BubbledState>());
    }

    void MaitaStateController::OnPopped()
    {
        if (m_pShoot) m_pShoot->SetEnabled(false);
        SetState(std::make_unique<PoppedState>(m_pFoodPool));
    }

    void MaitaStateController::SetState(std::unique_ptr<EnemyCharacterState> newState)
    {
        if (m_currentState)
            m_currentState->OnExit(this);
        m_currentState = std::move(newState);
        if (m_currentState)
            m_currentState->OnEnter(this);
    }
}