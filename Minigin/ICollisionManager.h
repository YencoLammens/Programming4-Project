#pragma once
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
    protected:
        ICollisionManager() = default;
    }