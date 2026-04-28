#include "ServiceLocator.h"
#include "NullSoundSystem.h"

namespace dae
{
    std::unique_ptr<SoundSystem> ServiceLocator::m_pSoundSystem{ std::make_unique<NullSoundSystem>() };

    SoundSystem& ServiceLocator::GetSoundSystem()
    {
        return *m_pSoundSystem;
    }

    void ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
    {
        if (ss)
        {
            m_pSoundSystem = std::move(ss);
        }
        else
        {
            m_pSoundSystem = std::make_unique<NullSoundSystem>();
        }
            
    }
}