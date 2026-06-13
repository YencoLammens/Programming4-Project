#include "NameEntryState.h"
#include "GameplayHelpers.h"
#include "HighScoreState.h"
#include "GameState.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "HighScoreManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "NameEntryComponent.h"
#include "MenuCommands.h"
#include "StopSoundCommand.h"
#include "Controller.h"
#include <SDL3/SDL.h>
#include <string>

void NameEntryState::OnEnter(int score)
{
    auto* fontLarge = dae::ResourceManager::GetInstance().LoadFont("PressStart2P.ttf", 36);

    auto titleGO = std::make_unique<dae::GameObject>();
    titleGO->GetTransform()->SetLocalPosition(430.f, 180.f, 0.f);
    titleGO->AddComponent<dae::TextComponent>("ENTER YOUR NAME", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(titleGO));

    auto scoreGO = std::make_unique<dae::GameObject>();
    scoreGO->GetTransform()->SetLocalPosition(455.f, 220.f, 0.f);
    const auto scoreStr = std::to_string(score);
    scoreGO->AddComponent<dae::TextComponent>("SCORE: " + std::string(scoreStr.size() < 6u ? 6u - scoreStr.size() : 0u, '0') + scoreStr, dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(scoreGO));

    auto displayGO = std::make_unique<dae::GameObject>();
    displayGO->GetTransform()->SetLocalPosition(310.f, 270.f, 0.f);
    auto* displayText = displayGO->AddComponent<dae::TextComponent>("[A]   A   A", fontLarge);
    dae::GameState::scene->Add(std::move(displayGO));

    auto hint1GO = std::make_unique<dae::GameObject>();
    hint1GO->GetTransform()->SetLocalPosition(420.f, 380.f, 0.f);
    hint1GO->AddComponent<dae::TextComponent>("W/UP: SCROLL UP", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(hint1GO));

    auto hint2GO = std::make_unique<dae::GameObject>();
    hint2GO->GetTransform()->SetLocalPosition(405.f, 410.f, 0.f);
    hint2GO->AddComponent<dae::TextComponent>("S/DOWN: SCROLL DOWN", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(hint2GO));

    auto hint3GO = std::make_unique<dae::GameObject>();
    hint3GO->GetTransform()->SetLocalPosition(385.f, 440.f, 0.f);
    hint3GO->AddComponent<dae::TextComponent>("A/D OR LEFT/RIGHT: MOVE", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(hint3GO));

    auto hint4GO = std::make_unique<dae::GameObject>();
    hint4GO->GetTransform()->SetLocalPosition(385.f, 470.f, 0.f);
    hint4GO->AddComponent<dae::TextComponent>("SPACE/ENTER/A: CONFIRM", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(hint4GO));

    auto nameEntryGO = std::make_unique<dae::GameObject>();
    auto* nameEntry = nameEntryGO->AddComponent<dae::NameEntryComponent>(
        displayText,
        [score](const std::string& name)
        {
            dae::HighScoreManager::Insert(dae::GameState::highScorePath, { name, score });
            dae::SceneManager::GetInstance().RequestTransition([]()
                {
                    NameEntryState::OnExit();
                    HighScoreState::OnEnter();
                });
        });
    dae::GameState::scene->Add(std::move(nameEntryGO));

    auto& input = dae::InputManager::GetInstance();
    input.BindCommand(SDL_SCANCODE_F2, dae::KeyState::Down, std::make_unique<dae::StopSoundCommand>());
    input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::ScrollUp));
    input.BindCommand(SDL_SCANCODE_UP, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::ScrollUp));
    input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::ScrollDown));
    input.BindCommand(SDL_SCANCODE_DOWN, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::ScrollDown));
    input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::CursorLeft));
    input.BindCommand(SDL_SCANCODE_LEFT, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::CursorLeft));
    input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::CursorRight));
    input.BindCommand(SDL_SCANCODE_RIGHT, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::CursorRight));
    input.BindCommand(SDL_SCANCODE_RETURN, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::Confirm));
    input.BindCommand(SDL_SCANCODE_SPACE, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::Confirm));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadUp, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::ScrollUp));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadDown, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::ScrollDown));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadLeft, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::CursorLeft));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadRight, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::CursorRight));
    input.BindCommand(0, dae::Controller::ControllerButton::ButtonA, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::Confirm));
    input.BindCommand(0, dae::Controller::ControllerButton::ButtonX, dae::KeyState::Down, std::make_unique<dae::NameEntryCommand>(nameEntry, dae::NameEntryAction::Confirm));
}

void NameEntryState::OnExit()
{
    dae::ClearGameScene();
}