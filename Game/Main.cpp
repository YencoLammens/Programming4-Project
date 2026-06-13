#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SDLSoundSystem.h"
#include "CollisionManager.h"
#include "GameState.h"
#include "MainMenuState.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
#ifdef _DEBUG
    dae::ServiceLocator::RegisterSoundSystem(
        std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
    dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif

    dae::ServiceLocator::GetSoundSystem().AddSound(0, "Data/Sounds/BubbleShoot.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(1, "Data/Sounds/BubblePop.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(2, "Data/Sounds/Score.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(4, "Data/Sounds/PlayerDeath.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(5, "Data/Sounds/PlayerHit.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(6, "Data/Sounds/Jump.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(7, "Data/Sounds/BoulderHit.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(8, "Data/Sounds/EnemyHit.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(9, "Data/Sounds/PickupDrop.mp3");
	dae::ServiceLocator::GetSoundSystem().AddSound(10, "Data/Sounds/BubbleBobbleTheme.mp3");

	dae::ServiceLocator::GetSoundSystem().PlayLooping(10, 0.1f);
    dae::ServiceLocator::RegisterCollisionManager(std::make_unique<dae::CollisionManager>());

    dae::GameState::scene = &dae::SceneManager::GetInstance().CreateScene();
    dae::GameState::fontArcade = dae::ResourceManager::GetInstance().LoadFont("PressStart2P.ttf", 12);
    dae::GameState::highScorePath = fs::exists(fs::path("Data")) ? "Data/Highscores.json" : "../Data/Highscores.json";

    MainMenuState::OnEnter();
}

int main(int, char* [])
{
#if __EMSCRIPTEN__
    fs::path data_location = "";
#else
    fs::path data_location = "./Data/";
    if (!fs::exists(data_location))
        data_location = "../Data/";
#endif
    dae::Minigin engine(data_location);
    engine.Run(load);
    return 0;
}