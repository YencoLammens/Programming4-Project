#include "ShootBubbleCommand.h"
#include "BubblePoolComponent.h"
#include "FacingComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "ServiceLocator.h"

namespace dae
{
    ShootBubbleCommand::ShootBubbleCommand(GameObject* player, BubblePoolComponent* pool)
        : GameObjectCommand(player), m_pool(pool), m_facing(player->GetComponent<FacingComponent>())
    {
    }

    void ShootBubbleCommand::Execute(float)
    {
        const float direction = m_facing->GetFacing();
		
        if (!m_pool->Acquire(GetGameObject()->GetTransform()->GetWorldPosition(), direction))
        {
            return;
        }
        ServiceLocator::GetSoundSystem().Play(1, 1.f);
    }
}