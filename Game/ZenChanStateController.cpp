#include "ZenChanStateController.h"
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
    ZenChanStateController::ZenChanStateController(GameObject* owner, std::unique_ptr<EnemyCharacterState> initialState, FoodPoolComponent* foodPool)
        : BaseComponent(owner), m_currentState(std::move(initialState)), m_pFoodPool(foodPool), m_hitbox(owner->GetComponent<HitboxComponent>()), m_physics(owner->GetComponent<PhysicsComponent>()), m_facing(owner->GetComponent<FacingComponent>()), m_render(owner->GetComponent<RenderComponent>()), m_animation(owner->GetComponent<AnimationComponent>())
    {
        if (m_currentState)
            m_currentState->OnEnter(this);
    }

    void ZenChanStateController::Update(float deltaTime)
    {
        if (!m_currentState) return;
        auto newState = m_currentState->Update(this, deltaTime);
        if (newState)
            SetState(std::move(newState));
    }

    void ZenChanStateController::OnBubbled()
    {
        SetState(std::make_unique<BubbledState>());
    }

    void ZenChanStateController::OnPopped()
    {
        SetState(std::make_unique<PoppedState>(m_pFoodPool));
    }

    void ZenChanStateController::SetState(std::unique_ptr<EnemyCharacterState> newState)
    {
        if (m_currentState)
            m_currentState->OnExit(this);
        m_currentState = std::move(newState);
        if (m_currentState)
            m_currentState->OnEnter(this);
    }
}