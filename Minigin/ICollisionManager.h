#pragma once
#include <vector>
#include "CollisionLayer.h"

namespace dae
{
    class HitboxComponent;
    class ICollisionManager
    {
    public:
        virtual ~ICollisionManager() = default;
        ICollisionManager(const ICollisionManager&) = delete;
        ICollisionManager& operator=(const ICollisionManager&) = delete;
        ICollisionManager(ICollisionManager&&) = delete;
        ICollisionManager& operator=(ICollisionManager&&) = delete;

        virtual void Register(HitboxComponent* hitbox) = 0;
        virtual void Unregister(HitboxComponent* hitbox) = 0;
        virtual void Update() = 0;
        virtual std::vector<HitboxComponent*> QueryLayer(CollisionLayer layer) const = 0;

    protected:
        ICollisionManager() = default;
    };
}       