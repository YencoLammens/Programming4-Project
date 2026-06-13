#include "MainMenuComponent.h"

namespace dae
{
    MainMenuComponent::MainMenuComponent(GameObject* owner, ModeSelectedFn onModeSelected)
        : BaseComponent(owner), m_onModeSelected(std::move(onModeSelected))
    {
    }

    void MainMenuComponent::SelectMode(GameMode mode, InputDevice device, unsigned int controllerIdx)
    {
        if (m_onModeSelected)
            m_onModeSelected(mode, device, controllerIdx);
    }
}