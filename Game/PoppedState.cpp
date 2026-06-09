#include "PoppedState.h"
#include "ZenChanStateController.h"
#include "HitboxComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "CollisionLayer.h"
#include "Transform.h"
#include "EventId.h"
#include "GameObject.h"

namespace dae
{
    PoppedState::PoppedState(float duration)
        : m_duration(duration)
    {
    }

    void PoppedState::OnEnter(ZenChanStateController* controller)
    {
        m_timer = 0.f;
        if (auto* hitbox = controller->GetHitboxComponent())   hitbox->SetLayer(CollisionLayer::None);
        if (auto* physics = controller->GetPhysicsComponent())  physics->SetEnabled(false);
        if (auto* anim = controller->GetAnimationComponent()) anim->Play(make_sdbm_hash("popped"));
    }

    std::unique_ptr<ZenChanCharacterState> PoppedState::Update(ZenChanStateController* controller, float deltaTime)
    {
        m_timer += deltaTime;

        auto* transform = controller->GetOwner()->GetTransform();
        auto pos = transform->GetLocalPosition();
        pos.y -= k_flySpeed * deltaTime;
        transform->SetLocalPosition(pos);

        if (m_timer >= m_duration && !controller->GetOwner()->IsMarkedForDeletion())
            controller->GetOwner()->MarkForDeletion();

        return nullptr;
    }

    void PoppedState::OnExit(ZenChanStateController*)
    {
    }
}