#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
    class ServiceLocator final
    {
    public:
        static SoundSystem& GetSoundSystem();
        static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);
    private:
        static std::unique_ptr<SoundSystem> m_pSoundSystem;
    };
}