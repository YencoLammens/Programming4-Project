#include "HitboxComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"

namespace dae
{
    HitboxComponent::HitboxComponent(GameObject* owner, float width, float height)
		: BaseComponent(owner), m_width(width), m_height(height), m_hitBox(owner->GetTransform()->GetWorldPosition().x, owner->GetTransform()->GetWorldPosition().y, width, height)
    {
    }

    void HitboxComponent::Update(const float)
    {
        auto pos = GetOwner()->GetTransform()->GetWorldPosition();
        m_hitBox.x = pos.x;
        m_hitBox.y = pos.y;
    }
    
    bool HitboxComponent::Overlaps(const HitboxComponent& other) const
    {  
        return IsOverlapping(m_hitBox, other.GetHitBox());
    }

}