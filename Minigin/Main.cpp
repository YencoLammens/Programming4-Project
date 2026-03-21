#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "Controller.h"
#include "HealthComponent.h"
#include "HealthDisplay.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"
#include "LoseHealthCommand.h"
#include "AddPointsCommand.h"


#include <filesystem>
namespace fs = std::filesystem;
	
static void load()
{
    //Scene setup
    auto& scene = dae::SceneManager::GetInstance().CreateScene();

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

    //Background
    auto go = std::make_unique<dae::GameObject>();
    auto* renderComponent = go->AddComponent<dae::RenderComponent>();
    renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.png"));
    scene.Add(std::move(go));

    //Assignment name
    go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(300, 20, 0);
    go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
    scene.Add(std::move(go));

    //DAE logo
    go = std::make_unique<dae::GameObject>();
    auto* renderComponent2 = go->AddComponent<dae::RenderComponent>();
    renderComponent2->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
    go->GetTransform()->SetLocalPosition(358, 180, 0);
    scene.Add(std::move(go));

    //FPS counter
    go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(10, 10, 0);
    go->AddComponent<dae::TextComponent>("FPS: ", font);
    go->AddComponent<dae::FPSComponent>();
    scene.Add(std::move(go));

    //Tutorial text
    go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(10, 80, 0);
    go->AddComponent<dae::TextComponent>("Controller: D-Pad to move Bobblun, X to lose health, A to gain points", fontSmall);
    scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(10, 100, 0);
    go->AddComponent<dae::TextComponent>("Keyboard: WASD to move Bubblun, C to lose health, X to gain points", fontSmall);
    scene.Add(std::move(go));

    //Player 1
    auto player1 = std::make_unique<dae::GameObject>();
    auto* renderComponent3 = player1->AddComponent<dae::RenderComponent>();
    renderComponent3->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Bubblun.png"));
    player1->GetTransform()->SetLocalPosition(300, 300, 0);
    auto* health1 = player1->AddComponent<dae::HealthComponent>(3);
    auto* score1 = player1->AddComponent<dae::ScoreComponent>();
    dae::GameObject* p1 = player1.get();
    scene.Add(std::move(player1));

    //Player 1 displays
    auto p1HealthDisplayGO = std::make_unique<dae::GameObject>();
    p1HealthDisplayGO->GetTransform()->SetLocalPosition(10, 140, 0);
    p1HealthDisplayGO->AddComponent<dae::TextComponent>("# lives: 3", fontSmall);
    p1HealthDisplayGO->AddComponent<dae::HealthDisplay>(health1, health1);
    scene.Add(std::move(p1HealthDisplayGO));

    auto p1ScoreDisplayGO = std::make_unique<dae::GameObject>();
    p1ScoreDisplayGO->GetTransform()->SetLocalPosition(10, 160, 0);
    p1ScoreDisplayGO->AddComponent<dae::TextComponent>("Score: 0", fontSmall);
    p1ScoreDisplayGO->AddComponent<dae::ScoreDisplay>(score1, score1);
    scene.Add(std::move(p1ScoreDisplayGO));

    //Player 2
    auto player2 = std::make_unique<dae::GameObject>();
    auto* renderComponent4 = player2->AddComponent<dae::RenderComponent>();
    renderComponent4->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Bobblun.png"));
    player2->GetTransform()->SetLocalPosition(500, 300, 0);
    auto* health2 = player2->AddComponent<dae::HealthComponent>(3);
    auto* score2 = player2->AddComponent<dae::ScoreComponent>();
    dae::GameObject* p2 = player2.get();
    scene.Add(std::move(player2));

    //Player 2 displays
    auto player2HealthDisplayGO = std::make_unique<dae::GameObject>();
    player2HealthDisplayGO->GetTransform()->SetLocalPosition(10, 180, 0);
    player2HealthDisplayGO->AddComponent<dae::TextComponent>("# lives: 3", fontSmall);
    player2HealthDisplayGO->AddComponent<dae::HealthDisplay>(health2, health2);
    scene.Add(std::move(player2HealthDisplayGO));

    auto player2ScoreDisplayGO = std::make_unique<dae::GameObject>();
    player2ScoreDisplayGO->GetTransform()->SetLocalPosition(10, 200, 0);
    player2ScoreDisplayGO->AddComponent<dae::TextComponent>("Score: 0", fontSmall);
    player2ScoreDisplayGO->AddComponent<dae::ScoreDisplay>(score2, score2);
    scene.Add(std::move(player2ScoreDisplayGO));

    //Keyboard inputs
    auto& input = dae::InputManager::GetInstance();
    //Movement
    input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 0, -1, 0 }, 100.f));
    input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 0,  1, 0 }, 100.f));
    input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ -1,  0, 0 }, 100.f));
    input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 1,  0, 0 }, 100.f));
    //Misc
    input.BindCommand(SDL_SCANCODE_C, dae::KeyState::Down, std::make_unique<dae::LoseHealthCommand>(p1, health1));
    input.BindCommand(SDL_SCANCODE_X, dae::KeyState::Down, std::make_unique<dae::AddPointsCommand>(p1, score1, 10));

    //Controller inputs
    //Movement
    input.BindCommand(0, dae::Controller::ControllerButton::DPadUp, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 0, -1, 0 }, 200.f));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadDown, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 0,  1, 0 }, 200.f));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadLeft, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ -1,  0, 0 }, 200.f));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadRight, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 1,  0, 0 }, 200.f));
    //Misc
    input.BindCommand(0, dae::Controller::ControllerButton::ButtonX, dae::KeyState::Down, std::make_unique<dae::LoseHealthCommand>(p2, health2));
    input.BindCommand(0, dae::Controller::ControllerButton::ButtonA, dae::KeyState::Down, std::make_unique<dae::AddPointsCommand>(p2, score2, 10));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
