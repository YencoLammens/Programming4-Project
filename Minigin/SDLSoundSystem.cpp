#include "SDLSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

namespace dae
{
    struct SoundRequest
    {
        sound_id id;
        float volume;
    };

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
            m_thread = std::jthread([this](std::stop_token st) { ProcessQueue(st); });
        }

        ~SDLSoundSystemImpl()
        {
            m_thread.request_stop();
            m_cv.notify_all();
            m_thread.join();

            //Seemingly gets cleaned up in minigin
            /*for (auto& [id, clip] : m_audioclips)
            {
                if (clip.pAudio)
                    MIX_DestroyAudio(clip.pAudio);
            }
            if (m_mixer)
                MIX_DestroyMixer(m_mixer);*/

            //MIX_Quit();
        }

        void Play(sound_id id, float volume)
        {
            {
                std::scoped_lock lock(m_queueMutex);
                m_requestQueue.push({ id, volume });
            }
            m_cv.notify_one();
        }

        void AddSound(sound_id id, const std::string& filePath)
        {
            std::scoped_lock lock(m_clipsMutex);
            m_audioclips[id] = AudioClip{ filePath, nullptr, false };
        }

    private:
        void ProcessQueue(std::stop_token st)
        {
            while (!st.stop_requested())
            {
                std::unique_lock lock(m_queueMutex);
                m_cv.wait(lock, st, [this] { return !m_requestQueue.empty(); });
                if (st.stop_requested())
                    return;
                auto request = m_requestQueue.front();
                m_requestQueue.pop();
                lock.unlock();
                std::scoped_lock clipsLock(m_clipsMutex);
                auto it = m_audioclips.find(request.id);
                if (it == m_audioclips.end())
                    continue;
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
                    MIX_SetMixerGain(m_mixer, request.volume);
                    if (!MIX_PlayAudio(m_mixer, clip.pAudio))
                        SDL_Log("MIX_PlayAudio failed: %s", SDL_GetError());
                }
            }
        }

        std::queue<SoundRequest> m_requestQueue;
        std::mutex m_queueMutex;
        std::mutex m_clipsMutex;
        std::condition_variable_any m_cv;
        std::unordered_map<sound_id, AudioClip> m_audioclips;
        MIX_Mixer* m_mixer{ nullptr };
        std::jthread m_thread;
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