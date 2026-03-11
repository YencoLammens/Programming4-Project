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
#include "TrashTheCacheComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "Controller.h"

#include <filesystem>
namespace fs = std::filesystem;
	
static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	
	auto go = std::make_unique<dae::GameObject>();
	auto* renderComponent = go->AddComponent<dae::RenderComponent>();
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.png"));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->GetTransform()->SetLocalPosition(80, 80, 0);
	go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto* renderComponent2 = go->AddComponent<dae::RenderComponent>();
	renderComponent2->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->GetTransform()->SetLocalPosition(358, 180, 0);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 10, 0);
	go->AddComponent<dae::TextComponent>("FPS: ", font);
	go->AddComponent<dae::FPSComponent>();
	scene.Add(std::move(go));

	auto player1 = std::make_unique<dae::GameObject>();
	auto* renderComponent3 = player1->AddComponent<dae::RenderComponent>();
	renderComponent3->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Bubblun.png"));
	player1->GetTransform()->SetLocalPosition(300, 300, 0);
	dae::GameObject* p1 = player1.get();
	scene.Add(std::move(player1));

	auto player2 = std::make_unique<dae::GameObject>();
	auto* renderComponent4 = player2->AddComponent<dae::RenderComponent>();
	renderComponent4->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Bobblun.png"));
	player2->GetTransform()->SetLocalPosition(500, 300, 0);
	dae::GameObject* p2 = player2.get();
	scene.Add(std::move(player2));

	auto& input = dae::InputManager::GetInstance();

	input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 0, -1, 0 }, 100.f));
	input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 0,  1, 0 }, 100.f));
	input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ -1,  0, 0 }, 100.f));
	input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 1,  0, 0 }, 100.f));

	input.BindCommand(0, dae::Controller::ControllerButton::DPadUp, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 0, -1, 0 }, 200.f));
	input.BindCommand(0, dae::Controller::ControllerButton::DPadDown, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 0,  1, 0 }, 200.f));
	input.BindCommand(0, dae::Controller::ControllerButton::DPadLeft, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ -1,  0, 0 }, 200.f));
	input.BindCommand(0, dae::Controller::ControllerButton::DPadRight, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 1,  0, 0 }, 200.f));
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
