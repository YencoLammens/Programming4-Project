#include "FiringState.h"
#include "IdleState.h"
#include "WalkingState.h"
#include "HurtState.h"
#include "PlayerStateController.h"
#include "AnimationComponent.h"
#include "FacingComponent.h"
#include "BubblePoolComponent.h"
#include "Transform.h"
#include "ServiceLocator.h"
#include "EventId.h"
#include "GameObject.h"

namespace dae
{
    FiringState::FiringState(float duration)
        : m_duration(duration)
    {
    }

    void FiringState::OnEnter(PlayerStateController* controller)
    {
        m_timer = 0.f;
        if (auto* anim = controller->GetAnimationComponent())
            anim->Play(make_sdbm_hash("fire"));
        auto* pool = controller->GetBubblePool();
        auto* facing = controller->GetFacingComponent();
        if (pool && facing)
        {
            const float direction = facing->GetFacing();
            if (pool->Acquire(controller->GetOwner()->GetTransform()->GetWorldPosition(), direction))
            {
                ServiceLocator::GetSoundSystem().Play(1, 1.f);
            }  
        }
    }

    std::unique_ptr<PlayerCharacterState> FiringState::Update(PlayerStateController* controller, float deltaTime)
    {
        m_timer += deltaTime;
        if (controller->WasHurtRequested())
            return std::make_unique<HurtState>();
        if (m_timer < m_duration)
            return nullptr;
        if (controller->IsMoving())
            return std::make_unique<WalkingState>();
        return std::make_unique<IdleState>();
    }

    void FiringState::OnExit(PlayerStateController*)
    {
    }
}