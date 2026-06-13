#pragma once
#include <functional>
#include <string>

namespace dae
{
    class Scene;
    class Font;

    enum class GameMode { SinglePlayer, Coop, Versus };

    enum class InputDevice { Keyboard, Controller };

    struct PlayerInputConfig
    {
        InputDevice device{ InputDevice::Keyboard };
        unsigned int controllerIndex{ 0 };
    };

    struct GameState
    {
        static inline int currentLevel{ 1 };
        static inline int hiScore{ 0 };
        static inline GameMode currentMode{ GameMode::SinglePlayer };
        static inline PlayerInputConfig p1Config{};
        static inline PlayerInputConfig p2Config{ InputDevice::Controller, 0 };
        static inline std::function<void()> onGameOver{};
        static inline Scene* scene{ nullptr };
        static inline Font* fontArcade{ nullptr };
        static inline std::string highScorePath;
    };
}