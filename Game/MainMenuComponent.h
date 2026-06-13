#pragma once
#include <functional>
#include "BaseComponent.h"
#include "GameState.h"

namespace dae
{
    class MainMenuComponent final : public BaseComponent
    {
    public:
        using ModeSelectedFn = std::function<void(GameMode, InputDevice, unsigned int)>;

        MainMenuComponent(GameObject* owner, ModeSelectedFn onModeSelected);
        ~MainMenuComponent() override = default;
        MainMenuComponent(const MainMenuComponent&) = delete;
        MainMenuComponent& operator=(const MainMenuComponent&) = delete;
        MainMenuComponent(MainMenuComponent&&) = delete;
        MainMenuComponent& operator=(MainMenuComponent&&) = delete;

        void Update(float) override {}
        void FixedUpdate(float) override {}

        void SelectMode(GameMode mode, InputDevice device, unsigned int controllerIdx);

    private:
        ModeSelectedFn m_onModeSelected;
    };
}