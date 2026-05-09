#pragma once
#include "ICollisionManager.h"
#include <vector>
#include <set>
#include <utility>
namespace dae
{
    class CollisionManager final : public ICollisionManager
    {
    public:
        void Register(HitboxComponent* hitbox) override;
        void Unregister(HitboxComponent* hitbox) override;
        void Update() override;
    private:
        std::vector<HitboxComponent*> m_hitboxes;
        std::set<std::pair<HitboxComponent*, HitboxComponent*>> m_activeOverlaps;
    };
}