#pragma once
#include "Command.h"
#include "SoundSystem.h"

namespace dae
{
    class PlaySoundCommand final : public Command
    {
    public:
        PlaySoundCommand(sound_id id, float volume);
        void Execute(float deltaTime) override;
    private:
        sound_id m_soundId;
        float m_volume;
    };
}