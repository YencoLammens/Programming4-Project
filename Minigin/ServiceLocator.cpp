#include "ServiceLocator.h"
#include "NullSoundSystem.h"
#include "NullCollisionManager.h"

namespace dae
{
    std::unique_ptr<SoundSystem> ServiceLocator::m_pSoundSystem{ std::make_unique<NullSoundSystem>() };
    std::unique_ptr<ICollisionManager> ServiceLocator::m_pCollisionManager{ std::make_unique<NullCollisionManager>() };

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

    ICollisionManager& ServiceLocator::GetCollisionManager()
    {
        return *m_pCollisionManager;
    }

    void ServiceLocator::RegisterCollisionManager(std::unique_ptr<ICollisionManager>&& cm)
    {
        if (cm)
        {
            m_pCollisionManager = std::move(cm);
        }
        else
        {
            m_pCollisionManager = std::make_unique<NullCollisionManager>();
        }
    }
}