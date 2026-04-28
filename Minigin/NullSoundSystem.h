#pragma once
#include "SoundSystem.h"

namespace dae
{
    class NullSoundSystem final : public SoundSystem
    {
    public:
        void Play(sound_id, float) override {}
        void AddSound(sound_id, const std::string&) override {}
    };
}