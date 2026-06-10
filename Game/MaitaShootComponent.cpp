#include "MaitaShootComponent.h"
#include "BoulderPoolComponent.h"
#include "FacingComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include <cstdlib>

namespace dae
{
    MaitaShootComponent::MaitaShootComponent(GameObject* owner, BoulderPoolComponent* boulderPool, FacingComponent* facing)
        : BaseComponent(owner), m_pBoulderPool(boulderPool), m_pFacing(facing)
    {
        m_shootInterval = k_minInterval + static_cast<float>(rand() % 3);
    }

    void MaitaShootComponent::Update(float deltaTime)
    {
        if (!m_enabled) return;

        m_shootTimer += deltaTime;
        if (m_shootTimer < m_shootInterval) return;

        m_shootTimer = 0.f;
        m_shootInterval = k_minInterval + static_cast<float>(rand() % 3);

        const float dir = m_pFacing ? m_pFacing->GetFacing() : 1.f;
        m_pBoulderPool->Acquire(GetOwner()->GetTransform()->GetWorldPosition(), dir);
    }
}