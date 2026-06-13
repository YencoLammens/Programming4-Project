#include "LoggingSoundSystem.h"
#ifdef _WIN32
#include <Windows.h>
#include <sstream>
#else 
#include <iostream>
#endif

namespace dae
{
    LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
        : m_pRealSoundSystem(std::move(ss))
    {
    }

    void LoggingSoundSystem::Play(sound_id id, float volume)
    {
        m_pRealSoundSystem->Play(id, volume);
#ifdef _WIN32
        std::stringstream ss;
        ss << "playing sound " << id << " at volume " << volume << "\n";
        OutputDebugStringA(ss.str().c_str());
#else
        std::cout << "playing sound " << id << " at volume " << volume << "\n";
#endif
    }

    void LoggingSoundSystem::PlayLooping(sound_id id, float volume)
    {
        m_pRealSoundSystem->PlayLooping(id, volume);
#ifdef _WIN32
        std::stringstream ss;
        ss << "looping sound " << id << " at volume " << volume << "\n";
        OutputDebugStringA(ss.str().c_str());
#else
        std::cout << "looping sound " << id << " at volume " << volume << "\n";
#endif
    }

    void LoggingSoundSystem::AddSound(sound_id id, const std::string& filePath)
    {
        m_pRealSoundSystem->AddSound(id, filePath);
#ifdef _WIN32
        std::stringstream ss;
        ss << "added sound " << id << " from path " << filePath << "\n";
        OutputDebugStringA(ss.str().c_str());
#else
        std::cout << "added sound " << id << " from path " << filePath << "\n";
#endif
    }
    void LoggingSoundSystem::ToggleMute()
    {
        m_pRealSoundSystem->ToggleMute();
#ifdef _WIN32
        std::stringstream ss;
        ss << "toggled mute\n";
        OutputDebugStringA(ss.str().c_str());
#else
        std::cout << "toggled mute\n";
#endif
    }
}