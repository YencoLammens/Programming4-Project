#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "InputManager.h"
#include "Controller.h"
#include "ServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SDLSoundSystem.h"
#include "CollisionManager.h"
#include "CollisionLayer.h"
#include "TilemapLoader.h"

//Commands
#include "MoveCommand.h"
#include "ShootBubbleCommand.h"
#include "JumpCommand.h"

//Components
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "HitboxComponent.h"
#include "BubblePoolComponent.h"
#include "FacingComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "CameraComponent.h"
#include "FoodPoolComponent.h"
#include "BoulderPoolComponent.h"
#include "MaitaShootComponent.h"

//Displays
#include "HealthDisplay.h"
#include "ScoreDisplay.h"

//Observers
#include "PlayerHitObserver.h"
#include "EnemyBubbledObserver.h"

//States
#include "WanderingState.h"
#include "IdleState.h"
#include "PlayerStateController.h"
#include "MaitaStateController.h"
#include "ZenChanStateController.h"

//Filesystem
#include <filesystem>
namespace fs = std::filesystem;


static void load()
{
    //Service locator + sound system setup
#ifdef _DEBUG
    dae::ServiceLocator::RegisterSoundSystem(
        std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
#else
    dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif

    //dae::ServiceLocator::GetSoundSystem().AddSound(0, "Data/Sounds/TestSong.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(0, "Data/Sounds/BubbleBobbleTheme.mp3");
	dae::ServiceLocator::GetSoundSystem().AddSound(1, "Data/Sounds/BubblePop.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(2, "Data/Sounds/Score.mp3");
    dae::ServiceLocator::GetSoundSystem().AddSound(3, "Data/Sounds/Death.mp3");
    // dae::ServiceLocator::GetSoundSystem().Play(0, 1.f);

    //Collision manager set up
    dae::ServiceLocator::RegisterCollisionManager(std::make_unique<dae::CollisionManager>());

    //-----------------------------------------------------------
    //Scene setup
    auto& scene = dae::SceneManager::GetInstance().CreateScene();

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto fontSmall = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
    auto fontArcade = dae::ResourceManager::GetInstance().LoadFont("PressStart2P.ttf", 12);

    //Background
    /*auto go = std::make_unique<dae::GameObject>();
    auto* renderComponent = go->AddComponent<dae::RenderComponent>();
    renderComponent->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.png"));
    scene.Add(std::move(go));*/

    //Level layout
    dae::TilemapLoader::Load(scene, "Data/Levels/level2.json");

    //Camera
    const float levelW = 512.f;
    const float levelH = 400.f;
    auto cameraGO = std::make_unique<dae::GameObject>();
    cameraGO->GetTransform()->SetLocalPosition(0.f, 0.f, 0.f);
    cameraGO->AddComponent<dae::CameraComponent>(1024.f, 576.f, levelW, levelH);
    scene.Add(std::move(cameraGO));

    
    //Assignment name
    /*go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(300, 20, 0);
    go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
    scene.Add(std::move(go));*/

    //DAE logo
    /*go = std::make_unique<dae::GameObject>();
    auto* renderComponent2 = go->AddComponent<dae::RenderComponent>();
    renderComponent2->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("logo.png"));
    go->GetTransform()->SetLocalPosition(358, 180, 0);
    scene.Add(std::move(go));*/

    //FPS counter
    /*auto go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(700, 10, 0);
    go->AddComponent<dae::TextComponent>("FPS: ", font);
    go->AddComponent<dae::FPSComponent>();
    scene.Add(std::move(go));*/

    //Tutorial text
    /*go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(10, 80, 0);
    go->AddComponent<dae::TextComponent>("Controller: D-Pad to move Bobblun, X to lose health, A to gain points", fontSmall);
    scene.Add(std::move(go));*/

    /*go = std::make_unique<dae::GameObject>();
    go->GetTransform()->SetLocalPosition(10, 100, 0);
    go->AddComponent<dae::TextComponent>("Keyboard: WASD to move Bubblun, C to lose health, X to gain points, SPACE to fire bubble", fontSmall);
    scene.Add(std::move(go));*/

    //-----------------------------------------------------------
    //object pools
    auto* bubbleTexture = dae::ResourceManager::GetInstance().LoadTexture("Bubble.png");
    auto bubblePoolGO = std::make_unique<dae::GameObject>();
    auto* bubblePoolPtr = bubblePoolGO->AddComponent<dae::BubblePoolComponent>(&scene, bubbleTexture);
    scene.Add(std::move(bubblePoolGO));

    auto* melonTexture = dae::ResourceManager::GetInstance().LoadTexture("MelonPickup.png");
    auto foodPoolGO = std::make_unique<dae::GameObject>();
    auto* melonFoodPool = foodPoolGO->AddComponent<dae::FoodPoolComponent>(&scene, melonTexture, 100);
    scene.Add(std::move(foodPoolGO));

    auto* friesTexture = dae::ResourceManager::GetInstance().LoadTexture("FriesPickup.png");
    auto friesPoolGO = std::make_unique<dae::GameObject>();
    auto* friesFoodPool = friesPoolGO->AddComponent<dae::FoodPoolComponent>(&scene, friesTexture, 200);
    scene.Add(std::move(friesPoolGO));

    auto* boulderTexture = dae::ResourceManager::GetInstance().LoadTexture("Boulder.png");
    auto boulderPoolGO = std::make_unique<dae::GameObject>();
    auto* boulderPool = boulderPoolGO->AddComponent<dae::BoulderPoolComponent>(&scene, boulderTexture);
    scene.Add(std::move(boulderPoolGO));

    //Player 1
    auto player1 = std::make_unique<dae::GameObject>();
    auto* renderComponent3 = player1->AddComponent<dae::RenderComponent>();
    renderComponent3->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("BubblunWalking.png"));
    player1->GetTransform()->SetLocalPosition(300, 300, 0);
    auto* health1 = player1->AddComponent<dae::HealthComponent>(3);
    auto* score1 = player1->AddComponent<dae::ScoreComponent>();
    auto* hitboxComponent1 = player1->AddComponent<dae::HitboxComponent>(16.f, 16.f);
    hitboxComponent1->SetLayer(dae::CollisionLayer::Player);
    auto* physics1 = player1->AddComponent<dae::PhysicsComponent>();
    player1->AddComponent<dae::FacingComponent>();
    auto* anim1 = player1->AddComponent<dae::AnimationComponent>(renderComponent3);
    anim1->AddClip(dae::make_sdbm_hash("idle"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunWalking.png"), 1, 16, 16, 0.15f});
    anim1->AddClip(dae::make_sdbm_hash("walk"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunWalking.png"), 4, 16, 16, 0.1f });
    anim1->AddClip(dae::make_sdbm_hash("jump"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunJump.png"), 4, 16, 16, 0.5f });
    anim1->AddClip(dae::make_sdbm_hash("fire"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunFire.png"), 1, 16, 16, 0.15f });
    anim1->AddClip(dae::make_sdbm_hash("hurt"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunHurt.png"), 4, 16, 16, 0.1f });
    anim1->AddClip(dae::make_sdbm_hash("dead"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunDead.png"), 4, 28, 32, 0.15f });
    anim1->Play(dae::make_sdbm_hash("idle"));
    auto* p1State = player1->AddComponent<dae::PlayerStateController>(std::make_unique<dae::IdleState>(), bubblePoolPtr);
    player1->AddComponent<dae::PlayerHitObserver>(hitboxComponent1, p1State);
    dae::GameObject* p1 = player1.get();
    scene.Add(std::move(player1));

    //Player 1 displays
    /*auto p1HealthDisplayGO = std::make_unique<dae::GameObject>();
    p1HealthDisplayGO->GetTransform()->SetLocalPosition(10, 140, 0);
    p1HealthDisplayGO->AddComponent<dae::TextComponent>("# lives: 3", fontSmall);
    p1HealthDisplayGO->AddComponent<dae::HealthDisplay>(health1, health1);
    scene.Add(std::move(p1HealthDisplayGO));

    auto p1ScoreDisplayGO = std::make_unique<dae::GameObject>();
    p1ScoreDisplayGO->GetTransform()->SetLocalPosition(10, 160, 0);
    p1ScoreDisplayGO->AddComponent<dae::TextComponent>("Score: 0", fontSmall);
    p1ScoreDisplayGO->AddComponent<dae::ScoreDisplay>(score1, score1);
    scene.Add(std::move(p1ScoreDisplayGO));*/
    auto p1LabelGO = std::make_unique<dae::GameObject>();
    p1LabelGO->GetTransform()->SetLocalPosition(40.f, 10.f, 0.f);
    p1LabelGO->AddComponent<dae::TextComponent>("1UP", fontArcade);
    scene.Add(std::move(p1LabelGO));

    auto p1ScoreDisplayGO = std::make_unique<dae::GameObject>();
    p1ScoreDisplayGO->GetTransform()->SetLocalPosition(40.f, 24.f, 0.f);
    p1ScoreDisplayGO->AddComponent<dae::TextComponent>("000000", fontArcade);
    p1ScoreDisplayGO->AddComponent<dae::ScoreDisplay>(score1, score1);
    scene.Add(std::move(p1ScoreDisplayGO));

    auto p1HealthDisplayGO = std::make_unique<dae::GameObject>();
    p1HealthDisplayGO->GetTransform()->SetLocalPosition(40.f, 38.f, 0.f);
    p1HealthDisplayGO->AddComponent<dae::TextComponent>("LIVES: 3", fontArcade);
    p1HealthDisplayGO->AddComponent<dae::HealthDisplay>(health1, health1);
    scene.Add(std::move(p1HealthDisplayGO));

    auto hiScoreLabelGO = std::make_unique<dae::GameObject>();
    hiScoreLabelGO->GetTransform()->SetLocalPosition(340.f, 30.f, 0.f);
    hiScoreLabelGO->AddComponent<dae::TextComponent>("HI-SCORE", fontArcade);
    scene.Add(std::move(hiScoreLabelGO));

    auto hiScoreGO = std::make_unique<dae::GameObject>();
    hiScoreGO->GetTransform()->SetLocalPosition(340.f, 50.f, 0.f);
    hiScoreGO->AddComponent<dae::TextComponent>("000000", fontArcade);
    scene.Add(std::move(hiScoreGO));

    //Player 2
    /*auto player2 = std::make_unique<dae::GameObject>();
    auto* renderComponent4 = player2->AddComponent<dae::RenderComponent>();
    renderComponent4->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Bobblun.png"));
    player2->GetTransform()->SetLocalPosition(500, 300, 0);
    auto* health2 = player2->AddComponent<dae::HealthComponent>(3);
    auto* score2 = player2->AddComponent<dae::ScoreComponent>();
    auto* hitboxComponent2 = player2->AddComponent<dae::HitboxComponent>(14.f, 14.f);
    hitboxComponent2->SetLayer(dae::CollisionLayer::Player);
    player2->AddComponent<dae::FacingComponent>();
    auto* p2State = player2->AddComponent<dae::PlayerStateController>(std::make_unique<dae::IdleState>(), bubblePoolPtr);
    player2->AddComponent<dae::PlayerHitObserver>(hitboxComponent2, p2State);
    dae::GameObject* p2 = player2.get();
    scene.Add(std::move(player2));*/

    //Player 2 displays
   /* auto player2HealthDisplayGO = std::make_unique<dae::GameObject>();
    player2HealthDisplayGO->GetTransform()->SetLocalPosition(10, 180, 0);
    player2HealthDisplayGO->AddComponent<dae::TextComponent>("# lives: 3", fontSmall);
    player2HealthDisplayGO->AddComponent<dae::HealthDisplay>(health2, health2);
    scene.Add(std::move(player2HealthDisplayGO));

    auto player2ScoreDisplayGO = std::make_unique<dae::GameObject>();
    player2ScoreDisplayGO->GetTransform()->SetLocalPosition(10, 200, 0);
    player2ScoreDisplayGO->AddComponent<dae::TextComponent>("Score: 0", fontSmall);
    player2ScoreDisplayGO->AddComponent<dae::ScoreDisplay>(score2, score2);
    scene.Add(std::move(player2ScoreDisplayGO));*/

    //Zennu channu
    auto enemy = std::make_unique<dae::GameObject>();
    auto* enemyRender = enemy->AddComponent<dae::RenderComponent>();
    enemyRender->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("ZenchanWalking.png"));
    enemy->GetTransform()->SetLocalPosition(100.f, 50.f, 0.f);
    auto* enemyHitbox = enemy->AddComponent<dae::HitboxComponent>(14.f, 14.f);
    enemyHitbox->SetLayer(dae::CollisionLayer::Enemy);
    enemy->AddComponent<dae::PhysicsComponent>();
    enemy->AddComponent<dae::FacingComponent>();
    auto* enemyAnim = enemy->AddComponent<dae::AnimationComponent>(enemyRender);
    enemyAnim->AddClip(dae::make_sdbm_hash("walk"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("ZenchanWalking.png"), 2, 16, 16, 0.15f });
    enemyAnim->AddClip(dae::make_sdbm_hash("bubbled"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("ZenchanBubbled.png"),  1, 16, 16, 0.2f });
    enemyAnim->AddClip(dae::make_sdbm_hash("popped"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("ZenchanPopped.png"),   4, 16, 16, 0.1f });
    enemyAnim->Play(dae::make_sdbm_hash("walk"));
    auto* enemyState = enemy->AddComponent<dae::ZenChanStateController>(std::make_unique<dae::WanderingState>(), melonFoodPool);
    enemy->AddComponent<dae::EnemyBubbledObserver>(enemyHitbox, enemyState);
    scene.Add(std::move(enemy));

    //Maita master of rock bender of none
    auto maita = std::make_unique<dae::GameObject>();
    auto* maitaRender = maita->AddComponent<dae::RenderComponent>();
    maitaRender->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("MaitaWalking.png"));
    maita->GetTransform()->SetLocalPosition(200.f, 50.f, 0.f);
    auto* maitaHitbox = maita->AddComponent<dae::HitboxComponent>(14.f, 14.f);
    maitaHitbox->SetLayer(dae::CollisionLayer::Enemy);
    maita->AddComponent<dae::PhysicsComponent>();
    auto* maitaFacing = maita->AddComponent<dae::FacingComponent>();
    auto* maitaAnim = maita->AddComponent<dae::AnimationComponent>(maitaRender);
    maitaAnim->AddClip(dae::make_sdbm_hash("walk"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("MaitaWalking.png"), 2, 16, 16, 0.15f });
    maitaAnim->AddClip(dae::make_sdbm_hash("bubbled"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("MaitaBubbled.png"), 1, 16, 16, 0.2f });
    maitaAnim->AddClip(dae::make_sdbm_hash("popped"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("MaitaPopped.png"), 4, 16, 16, 0.1f });
    maitaAnim->Play(dae::make_sdbm_hash("walk"));
    auto* maitaShoot = maita->AddComponent<dae::MaitaShootComponent>(boulderPool, maitaFacing);
    auto* maitaState = maita->AddComponent<dae::MaitaStateController>(std::make_unique<dae::WanderingState>(100.f), friesFoodPool, maitaShoot);
    maita->AddComponent<dae::EnemyBubbledObserver>(maitaHitbox, maitaState);
    scene.Add(std::move(maita));


    //-----------------------------------------------------------
    //Keyboard inputs
    auto& input = dae::InputManager::GetInstance();
    //Movement
    //input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 0, -1, 0 }, 100.f));
    input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Down, std::make_unique<dae::JumpCommand>(p1, physics1, p1State));
    //input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 0,  1, 0 }, 100.f));
    input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ -1, 0, 0 }, 100.f, p1State));
    input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p1, glm::vec3{ 1, 0, 0 }, 100.f, p1State));
    //Misc
    input.BindCommand(SDL_SCANCODE_SPACE, dae::KeyState::Down, std::make_unique<dae::ShootBubbleCommand>(p1, p1State));

    //Controller inputs
    //Movement
   /* input.BindCommand(0, dae::Controller::ControllerButton::DPadUp, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 0, -1, 0 }, 200.f));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadDown, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 0,  1, 0 }, 200.f));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadLeft, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ -1,  0, 0 }, 200.f));
    input.BindCommand(0, dae::Controller::ControllerButton::DPadRight, dae::KeyState::Pressed, std::make_unique<dae::MoveCommand>(p2, glm::vec3{ 1,  0, 0 }, 200.f));*/
    //Misc
    /*input.BindCommand(0, dae::Controller::ControllerButton::ButtonY, dae::KeyState::Down, std::make_unique<dae::ShootBubbleCommand>(p2, bubblePoolPtr));*/

    //Sound test
    //input.BindCommand(SDL_SCANCODE_Z, dae::KeyState::Down, std::make_unique<dae::PlaySoundCommand>(0, 1.0f));

    //input.BindCommand(SDL_SCANCODE_B, dae::KeyState::Down, std::make_unique<dae::BubbleHitCommand>(enemyPtr, enemyState));
    
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
