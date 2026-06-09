#pragma once
#include "ICollisionManager.h"
namespace dae
{
    class NullCollisionManager final : public ICollisionManager
    {
    public:
        void Register(HitboxComponent*) override {}
        void Unregister(HitboxComponent*) override {}
        void Update() override {}
        std::vector<HitboxComponent*> QueryLayer(CollisionLayer) const override { return {}; }

    };
}