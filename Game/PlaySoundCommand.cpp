#include "PlaySoundCommand.h"
#include "ServiceLocator.h"

namespace dae
{
    PlaySoundCommand::PlaySoundCommand(sound_id id, float volume)
        : m_soundId(id), m_volume(volume)
    {
    }

    void PlaySoundCommand::Execute(float)
    {
        ServiceLocator::GetSoundSystem().Play(m_soundId, m_volume);
    }
}