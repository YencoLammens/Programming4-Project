#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
    class LoggingSoundSystem final : public SoundSystem
    {
    public:
        explicit LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss);
        ~LoggingSoundSystem() override = default;
        LoggingSoundSystem(const LoggingSoundSystem&) = delete;
        LoggingSoundSystem& operator=(const LoggingSoundSystem&) = delete;
        LoggingSoundSystem(LoggingSoundSystem&&) = delete;
        LoggingSoundSystem& operator=(LoggingSoundSystem&&) = delete;
        void Play(sound_id id, float volume) override;
        void AddSound(sound_id id, const std::string& filePath) override;
        void ToggleMute() override;
    private:
        std::unique_ptr<SoundSystem> m_pRealSoundSystem;
    };
}