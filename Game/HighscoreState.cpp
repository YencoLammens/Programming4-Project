#include "HighScoreState.h"
#include "GameplayHelpers.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "HighScoreManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "MenuCommands.h"
#include "StopSoundCommand.h"
#include "Controller.h"
#include <SDL3/SDL.h>
#include <string>

void HighScoreState::OnEnter()
{
    auto titleGO = std::make_unique<dae::GameObject>();
    titleGO->GetTransform()->SetLocalPosition(420.f, 40.f, 0.f);
    titleGO->AddComponent<dae::TextComponent>("HIGH SCORES", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(titleGO));

    const auto entries = dae::HighScoreManager::Load(dae::GameState::highScorePath);
    for (int i = 0; i < static_cast<int>(entries.size()); ++i)
    {
        const auto& e = entries[i];
        const auto entryScoreStr = std::to_string(e.score);
        const std::string line = std::to_string(i + 1) + ".  " + e.name + "   "
            + std::string(entryScoreStr.size() < 6u ? 6u - entryScoreStr.size() : 0u, '0') + entryScoreStr;
        auto entryGO = std::make_unique<dae::GameObject>();
        entryGO->GetTransform()->SetLocalPosition(380.f, static_cast<float>(80 + i * 40), 0.f);
        entryGO->AddComponent<dae::TextComponent>(line, dae::GameState::fontArcade);
        dae::GameState::scene->Add(std::move(entryGO));
    }

    auto promptGO = std::make_unique<dae::GameObject>();
    promptGO->GetTransform()->SetLocalPosition(380.f, 530.f, 0.f);
    promptGO->AddComponent<dae::TextComponent>("PRESS ANY BUTTON", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(promptGO));

    auto& input = dae::InputManager::GetInstance();
    input.BindCommand(SDL_SCANCODE_F2, dae::KeyState::Down, std::make_unique<dae::StopSoundCommand>());

    auto goToMenu = []()
        {
            dae::SceneManager::GetInstance().RequestTransition([]() { HighScoreState::OnExit(); MainMenuState::OnEnter(); });
        };
    input.BindCommand(SDL_SCANCODE_SPACE, dae::KeyState::Down, std::make_unique<dae::LambdaCommand>(goToMenu));
    input.BindCommand(SDL_SCANCODE_RETURN, dae::KeyState::Down, std::make_unique<dae::LambdaCommand>(goToMenu));
    input.BindCommand(SDL_SCANCODE_ESCAPE, dae::KeyState::Down, std::make_unique<dae::LambdaCommand>(goToMenu));
    input.BindCommand(0, dae::Controller::ControllerButton::ButtonA, dae::KeyState::Down, std::make_unique<dae::LambdaCommand>(goToMenu));
    input.BindCommand(1, dae::Controller::ControllerButton::ButtonA, dae::KeyState::Down, std::make_unique<dae::LambdaCommand>(goToMenu));
}

void HighScoreState::OnExit()
{
    dae::ClearGameScene();
}