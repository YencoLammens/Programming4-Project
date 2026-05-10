#pragma once
#include "SoundSystem.h"
#include "ICollisionManager.h"
#include <memory>

namespace dae
{
    class ServiceLocator final
    {
    public:
        static SoundSystem& GetSoundSystem();
        static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);

        static ICollisionManager& GetCollisionManager();
        static void RegisterCollisionManager(std::unique_ptr<ICollisionManager>&& cm);
    private:
        static std::unique_ptr<SoundSystem> m_pSoundSystem;
        static std::unique_ptr<ICollisionManager> m_pCollisionManager;
    };
}