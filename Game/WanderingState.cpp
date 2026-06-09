#include "WanderingState.h"
#include "ZenChanStateController.h"
#include "HitboxComponent.h"
#include "PhysicsComponent.h"
#include "FacingComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "ServiceLocator.h"
#include "ICollisionManager.h"
#include "CollisionLayer.h"
#include "EventId.h"

namespace dae
{
    WanderingState::WanderingState(float speed)
        : m_speed(speed)
    {
    }

    void WanderingState::OnEnter(ZenChanStateController* controller)
    {
        m_direction = 1.f;
        if (auto* anim = controller->GetAnimationComponent())
            anim->Play(make_sdbm_hash("walk"));
    }

    std::unique_ptr<ZenChanCharacterState> WanderingState::Update(ZenChanStateController* controller, float)
    {
        if (auto* hitbox = controller->GetHitboxComponent())
        {
            const auto rect = hitbox->GetHitBox();
            const auto walls = ServiceLocator::GetCollisionManager().QueryLayer(CollisionLayer::Wall);

            for (const auto* wall : walls)
            {
                const auto w = wall->GetHitBox();
                if (rect.y + rect.height <= w.y || rect.y >= w.y + w.height)
                    continue;
                if (m_direction > 0.f && rect.x + rect.width + k_wallMargin >= w.x && rect.x < w.x)
                {
                    m_direction = -1.f;
                    break;
                }
                else if (m_direction < 0.f && rect.x - k_wallMargin <= w.x + w.width && rect.x + rect.width > w.x + w.width)
                {
                    m_direction = 1.f;
                    break;
                }
            }
        }

        if (auto* facing = controller->GetFacingComponent())  facing->SetFacing(m_direction);
        if (auto* render = controller->GetRenderComponent())   render->SetFlipX(m_direction > 0.f);
        if (auto* physics = controller->GetPhysicsComponent())  physics->SetHorizontalVelocity(m_direction * m_speed);

        return nullptr;
    }

    void WanderingState::OnExit(ZenChanStateController*)
    {
    }
}