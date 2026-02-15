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
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	
	auto go = std::make_unique<dae::GameObject>();
	auto* renderComponent = go->AddComponent<dae::RenderComponent>();  // auto* not auto&
	renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.png"));
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->GetTransform()->SetLocalPosition(80, 80, 0);
	go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	auto* renderComponent2 = go->AddComponent<dae::RenderComponent>();  // New variable name
	renderComponent2->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->GetTransform()->SetLocalPosition(358, 180, 0);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->GetTransform()->SetLocalPosition(10, 10, 0);
	go->AddComponent<dae::TextComponent>("FPS: ", font);
	go->AddComponent<dae::FPSComponent>();
	scene.Add(std::move(go));
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
