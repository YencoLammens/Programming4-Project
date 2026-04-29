#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
    class SDLSoundSystem final : public SoundSystem
    {
    public:
        SDLSoundSystem();
        ~SDLSoundSystem() override;
        SDLSoundSystem(const SDLSoundSystem&) = delete;
        SDLSoundSystem& operator=(const SDLSoundSystem&) = delete;
        SDLSoundSystem(SDLSoundSystem&&) = delete;
        SDLSoundSystem& operator=(SDLSoundSystem&&) = delete;
        void Play(sound_id id, float volume) override;
        void AddSound(sound_id id, const std::string& filePath) override;
    private:
        class SDLSoundSystemImpl;
        std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
    };
}