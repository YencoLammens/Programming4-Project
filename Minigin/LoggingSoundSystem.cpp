#include "LoggingSoundSystem.h"
#include <Windows.h>
#include <sstream>

namespace dae
{
    LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
        : m_pRealSoundSystem(std::move(ss))
    {
    }

    void LoggingSoundSystem::Play(sound_id id, float volume)
    {
        m_pRealSoundSystem->Play(id, volume);
        std::stringstream ss;
        ss << "playing sound " << id << " at volume " << volume << "\n";
        OutputDebugStringA(ss.str().c_str());
    }

    void LoggingSoundSystem::AddSound(sound_id id, const std::string& filePath)
    {
        m_pRealSoundSystem->AddSound(id, filePath);
        std::stringstream ss;
        ss << "added sound " << id << " from path " << filePath << "\n";
        OutputDebugStringA(ss.str().c_str());
    }
}