#include "SDLSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map>
#include <string>

namespace dae
{
    class SDLSoundSystem::SDLSoundSystemImpl
    {
        struct AudioClip
        {
            std::string filePath;
            MIX_Audio* pAudio{ nullptr };
            bool isLoaded{ false };
        };

    public:
        SDLSoundSystemImpl()
        {
            if (!MIX_Init())
            {
                SDL_Log("SDL_mixer MIX_Init failed: %s", SDL_GetError());
            }

            m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
            if (!m_mixer)
            {
                SDL_Log("MIX_CreateMixerDevice failed: %s", SDL_GetError());
            }
        }

        ~SDLSoundSystemImpl()
        {
            MIX_Quit();
        }

        void Play(sound_id id, float volume)
        {
            auto it = m_audioclips.find(id);
            if (it == m_audioclips.end())
                return;
            auto& clip = it->second;
            if (!clip.isLoaded)
            {
                clip.pAudio = MIX_LoadAudio(m_mixer, clip.filePath.c_str(), false);
                clip.isLoaded = true;
                if (!clip.pAudio)
                    SDL_Log("MIX_LoadAudio failed for '%s': %s", clip.filePath.c_str(), SDL_GetError());
            }
            if (clip.pAudio && m_mixer)
            {
				MIX_SetMixerGain(m_mixer, volume);
                if (!MIX_PlayAudio(m_mixer, clip.pAudio))
                    SDL_Log("MIX_PlayAudio failed: %s", SDL_GetError());
            }
        }

        void AddSound(sound_id id, const std::string& filePath)
        {
            m_audioclips[id] = AudioClip{ filePath, nullptr, false };
        }

    private:
        std::unordered_map<sound_id, AudioClip> m_audioclips;
        MIX_Mixer* m_mixer{ nullptr };
    };

    SDLSoundSystem::SDLSoundSystem()
        : m_pImpl(std::make_unique<SDLSoundSystemImpl>())
    {
    }

    SDLSoundSystem::~SDLSoundSystem() = default;

    void SDLSoundSystem::Play(sound_id id, float volume)
    {
        m_pImpl->Play(id, volume);
    }

    void SDLSoundSystem::AddSound(sound_id id, const std::string& filePath)
    {
        m_pImpl->AddSound(id, filePath);
    }
}