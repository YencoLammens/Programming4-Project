#include "MainMenuState.h"
#include "GameplayHelpers.h"
#include "SingleplayerGameState.h"
#include "MultiplayerGameState.h"
#include "VersusGameState.h"
#include "GameState.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "MainMenuComponent.h"
#include "MenuCommands.h"
#include "StopSoundCommand.h"
#include "Controller.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include <SDL3/SDL.h>

void MainMenuState::OnEnter()
{
    auto menuGO = std::make_unique<dae::GameObject>();
    auto* menuComp = menuGO->AddComponent<dae::MainMenuComponent>(
        [](dae::GameMode mode, dae::InputDevice device, unsigned int ctrlIdx)
        {
            dae::GameState::currentMode = mode;
            if (mode == dae::GameMode::SinglePlayer)
            {
                dae::GameState::p1Config = { device, ctrlIdx };
                dae::SceneManager::GetInstance().RequestTransition([]() { OnExit(); SingleplayerGameState::OnEnter(); });
            }
            else if (mode == dae::GameMode::Coop)
            {
                dae::GameState::p1Config = { dae::InputDevice::Keyboard, 0 };
                dae::GameState::p2Config = { dae::InputDevice::Controller, 0 };
                dae::SceneManager::GetInstance().RequestTransition([]() { OnExit(); MultiplayerGameState::OnEnter(); });;
            }
            else
            {
                dae::GameState::p1Config = { dae::InputDevice::Keyboard, 0 };
                dae::GameState::p2Config = { dae::InputDevice::Controller, 0 };
                dae::SceneManager::GetInstance().RequestTransition([]() { OnExit(); VersusGameState::OnEnter(); });
            }
        });
    dae::GameState::scene->Add(std::move(menuGO));

	auto logoGO = std::make_unique<dae::GameObject>();
	logoGO->GetTransform()->SetLocalPosition(350.f, 100.f, 0.f);
    auto* renderComponent = logoGO->AddComponent<dae::RenderComponent>();
    renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Titlecard.png"));
    dae::GameState::scene->Add(std::move(logoGO));

    auto spGO = std::make_unique<dae::GameObject>();
    spGO->GetTransform()->SetLocalPosition(350, 390.f, 0.f);
    spGO->AddComponent<dae::TextComponent>("A OR <- FOR SINGLEPLAYER", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(spGO));

    auto mpGO = std::make_unique<dae::GameObject>();
    mpGO->GetTransform()->SetLocalPosition(360, 430.f, 0.f);
    mpGO->AddComponent<dae::TextComponent>("Z OR ^ FOR MULTIPLAYER", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(mpGO));

    auto vsGO = std::make_unique<dae::GameObject>();
    vsGO->GetTransform()->SetLocalPosition(375.f, 470.f, 0.f);
    vsGO->AddComponent<dae::TextComponent>("D OR -> FOR VERSUS", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(vsGO));

    auto& input = dae::InputManager::GetInstance();
    input.BindCommand(SDL_SCANCODE_F2, dae::KeyState::Down, std::make_unique<dae::StopSoundCommand>());
    input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Down, std::make_unique<dae::SelectModeCommand>(menuComp, dae::GameMode::SinglePlayer, dae::InputDevice::Keyboard));
    input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Down, std::make_unique<dae::SelectModeCommand>(menuComp, dae::GameMode::Coop, dae::InputDevice::Keyboard));
    input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Down, std::make_unique<dae::SelectModeCommand>(menuComp, dae::GameMode::Versus, dae::InputDevice::Keyboard));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadLeft, dae::KeyState::Down, std::make_unique<dae::SelectModeCommand>(menuComp, dae::GameMode::SinglePlayer, dae::InputDevice::Controller, 0));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadUp, dae::KeyState::Down, std::make_unique<dae::SelectModeCommand>(menuComp, dae::GameMode::Coop, dae::InputDevice::Controller, 0));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadRight, dae::KeyState::Down, std::make_unique<dae::SelectModeCommand>(menuComp, dae::GameMode::Versus, dae::InputDevice::Controller, 0));
}

void MainMenuState::OnExit()
{
    dae::ClearGameScene();
}