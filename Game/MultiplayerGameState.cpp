#include "MultiplayerGameState.h"
#include "GameplayHelpers.h"
#include "NameEntryState.h"
#include "GameState.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "HitboxComponent.h"
#include "BubblePoolComponent.h"
#include "FacingComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "CameraComponent.h"
#include "LevelManagerComponent.h"
#include "FoodPoolComponent.h"
#include "BoulderPoolComponent.h"
#include "PlayerStateController.h"
#include "PlayerHitObserver.h"
#include "IdleState.h"
#include "CollisionLayer.h"
#include "HealthDisplay.h"
#include "ScoreDisplay.h"
#include "StopSoundCommand.h"
#include "SkipLevelCommand.h"
#include "TilemapLoader.h"
#include "EventId.h"
#include <SDL3/SDL.h>
#include <string>

namespace
{
    dae::GameObject* s_p1{ nullptr };
    dae::GameObject* s_p2{ nullptr };
    dae::ScoreComponent* s_score1{ nullptr };
    dae::LevelManagerComponent* s_levelMgr{ nullptr };
    dae::FoodPoolComponent* s_melonFood{ nullptr };
    dae::FoodPoolComponent* s_friesFood{ nullptr };
    dae::BoulderPoolComponent* s_boulderPool{ nullptr };
    dae::TextComponent* s_hiScoreText{ nullptr };
    dae::BubblePoolComponent* s_bubblePool{ nullptr };

    void OnLevelComplete()
    {
        dae::GameState::currentLevel = dae::GameState::currentLevel < 3 ? dae::GameState::currentLevel + 1 : 1;
        const int s = s_score1->GetScore();
        if (s > dae::GameState::hiScore)
        {
            dae::GameState::hiScore = s;
            const auto str = std::to_string(s);
            s_hiScoreText->SetText(std::string(str.size() < 6u ? 6u - str.size() : 0u, '0') + str);
        }
        s_p1->GetTransform()->SetLocalPosition(20.f, 340.f, 0.f);
        s_bubblePool->ReturnAll();
        s_melonFood->ReturnAll();
        s_friesFood->ReturnAll();
        s_boulderPool->ReturnAll();
        if (s_p2) s_p2->GetTransform()->SetLocalPosition(460.f, 340.f, 0.f);
        const auto nextSpawns = dae::TilemapLoader::Load(*dae::GameState::scene, "Data/Levels/level" + std::to_string(dae::GameState::currentLevel) + ".json");
        dae::SpawnEnemiesFromData(nextSpawns, *dae::GameState::scene, s_levelMgr, s_melonFood, s_friesFood, s_boulderPool);
    }

    void OnSkipLevel()
    {
        dae::GameState::currentLevel = dae::GameState::currentLevel < 3 ? dae::GameState::currentLevel + 1 : 1;
        s_p1->GetTransform()->SetLocalPosition(20.f, 340.f, 0.f);
        if (s_p2) s_p2->GetTransform()->SetLocalPosition(460.f, 340.f, 0.f);
        const auto spawns = dae::TilemapLoader::Load(*dae::GameState::scene, "Data/Levels/level" + std::to_string(dae::GameState::currentLevel) + ".json");
        dae::SpawnEnemiesFromData(spawns, *dae::GameState::scene, s_levelMgr, s_melonFood, s_friesFood, s_boulderPool);
    }
}

void MultiplayerGameState::OnEnter()
{
    dae::GameState::currentLevel = 1;

    auto initialSpawns = dae::TilemapLoader::Load(*dae::GameState::scene, "Data/Levels/level" + std::to_string(dae::GameState::currentLevel) + ".json");

    auto cameraGO = std::make_unique<dae::GameObject>();
    cameraGO->GetTransform()->SetLocalPosition(0.f, 0.f, 0.f);
    cameraGO->AddComponent<dae::CameraComponent>(1024.f, 576.f, 512.f, 400.f);
    dae::GameState::scene->Add(std::move(cameraGO));

    auto* bubbleTexture = dae::ResourceManager::GetInstance().LoadTexture("Bubble.png");
    auto bubblePoolGO = std::make_unique<dae::GameObject>();
    auto* bubblePoolPtr = bubblePoolGO->AddComponent<dae::BubblePoolComponent>(dae::GameState::scene, bubbleTexture);
    s_bubblePool = bubblePoolPtr;
    dae::GameState::scene->Add(std::move(bubblePoolGO));

    auto* melonTexture = dae::ResourceManager::GetInstance().LoadTexture("MelonPickup.png");
    auto melonFoodPoolGO = std::make_unique<dae::GameObject>();
    s_melonFood = melonFoodPoolGO->AddComponent<dae::FoodPoolComponent>(dae::GameState::scene, melonTexture, 100);
    dae::GameState::scene->Add(std::move(melonFoodPoolGO));

    auto* friesTexture = dae::ResourceManager::GetInstance().LoadTexture("FriesPickup.png");
    auto friesFoodPoolGO = std::make_unique<dae::GameObject>();
    s_friesFood = friesFoodPoolGO->AddComponent<dae::FoodPoolComponent>(dae::GameState::scene, friesTexture, 200);
    dae::GameState::scene->Add(std::move(friesFoodPoolGO));

    auto* boulderTexture = dae::ResourceManager::GetInstance().LoadTexture("Boulder.png");
    auto boulderPoolGO = std::make_unique<dae::GameObject>();
    s_boulderPool = boulderPoolGO->AddComponent<dae::BoulderPoolComponent>(dae::GameState::scene, boulderTexture);
    dae::GameState::scene->Add(std::move(boulderPoolGO));

    auto player1 = std::make_unique<dae::GameObject>();
    auto* renderComponent3 = player1->AddComponent<dae::RenderComponent>();
    renderComponent3->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("BubblunWalking.png"));
    player1->GetTransform()->SetLocalPosition(20.f, 340.f, 0.f);
    auto* health1 = player1->AddComponent<dae::HealthComponent>(3);
    s_score1 = player1->AddComponent<dae::ScoreComponent>();
    auto* hitboxComponent1 = player1->AddComponent<dae::HitboxComponent>(16.f, 16.f);
    hitboxComponent1->SetLayer(dae::CollisionLayer::Player);
    auto* physics1 = player1->AddComponent<dae::PhysicsComponent>();
    player1->AddComponent<dae::FacingComponent>();
    auto* anim1 = player1->AddComponent<dae::AnimationComponent>(renderComponent3);
    anim1->AddClip(dae::make_sdbm_hash("idle"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunWalking.png"), 1, 16, 16, 0.15f });
    anim1->AddClip(dae::make_sdbm_hash("walk"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunWalking.png"), 4, 16, 16, 0.1f });
    anim1->AddClip(dae::make_sdbm_hash("jump"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunJump.png"), 4, 16, 16, 0.5f });
    anim1->AddClip(dae::make_sdbm_hash("fire"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunFire.png"), 1, 16, 16, 0.15f });
    anim1->AddClip(dae::make_sdbm_hash("hurt"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunHurt.png"), 4, 16, 16, 0.1f });
    anim1->AddClip(dae::make_sdbm_hash("dead"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BubblunDead.png"), 4, 28, 32, 0.15f });
    anim1->Play(dae::make_sdbm_hash("idle"));
    auto* p1State = player1->AddComponent<dae::PlayerStateController>(std::make_unique<dae::IdleState>(), bubblePoolPtr);
    player1->AddComponent<dae::PlayerHitObserver>(hitboxComponent1, p1State);
    p1State->SetSpawnPosition({ 20.f, 340.f, 0.f });
    s_p1 = player1.get();
    dae::GameState::scene->Add(std::move(player1));

    auto player2 = std::make_unique<dae::GameObject>();
    auto* renderComponent4 = player2->AddComponent<dae::RenderComponent>();
    renderComponent4->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("BobblunWalking.png"));
    player2->GetTransform()->SetLocalPosition(460.f, 340.f, 0.f);
    auto* health2 = player2->AddComponent<dae::HealthComponent>(3);
    auto* score2 = player2->AddComponent<dae::ScoreComponent>();
    auto* hitboxComponent2 = player2->AddComponent<dae::HitboxComponent>(16.f, 16.f);
    hitboxComponent2->SetLayer(dae::CollisionLayer::Player);
    auto* p2Physics = player2->AddComponent<dae::PhysicsComponent>();
    player2->AddComponent<dae::FacingComponent>();
    auto* anim2 = player2->AddComponent<dae::AnimationComponent>(renderComponent4);
    anim2->AddClip(dae::make_sdbm_hash("idle"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BobblunWalking.png"), 1, 16, 16, 0.15f });
    anim2->AddClip(dae::make_sdbm_hash("walk"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BobblunWalking.png"), 4, 16, 16, 0.1f });
    anim2->AddClip(dae::make_sdbm_hash("jump"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BobblunJump.png"), 4, 16, 16, 0.5f });
    anim2->AddClip(dae::make_sdbm_hash("fire"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BobblunFire.png"), 1, 16, 16, 0.15f });
    anim2->AddClip(dae::make_sdbm_hash("hurt"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BobblunHurt.png"), 4, 16, 16, 0.1f });
    anim2->AddClip(dae::make_sdbm_hash("dead"), dae::AnimationClip{ dae::ResourceManager::GetInstance().LoadTexture("BobblunDead.png"), 4, 28, 32, 0.15f });
    anim2->Play(dae::make_sdbm_hash("idle"));
    auto* p2State = player2->AddComponent<dae::PlayerStateController>(std::make_unique<dae::IdleState>(), bubblePoolPtr);
    player2->AddComponent<dae::PlayerHitObserver>(hitboxComponent2, p2State);
    p2State->SetSpawnPosition({ 460.f, 340.f, 0.f });
    s_p2 = player2.get();
    dae::GameState::scene->Add(std::move(player2));

    auto p1LabelGO = std::make_unique<dae::GameObject>();
    p1LabelGO->GetTransform()->SetLocalPosition(40.f, 20.f, 0.f);
    p1LabelGO->AddComponent<dae::TextComponent>("1UP", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(p1LabelGO));

    auto p1ScoreDisplayGO = std::make_unique<dae::GameObject>();
    p1ScoreDisplayGO->GetTransform()->SetLocalPosition(40.f, 34.f, 0.f);
    p1ScoreDisplayGO->AddComponent<dae::TextComponent>("000000", dae::GameState::fontArcade);
    p1ScoreDisplayGO->AddComponent<dae::ScoreDisplay>(s_score1, s_score1);
    dae::GameState::scene->Add(std::move(p1ScoreDisplayGO));

    auto p1HealthDisplayGO = std::make_unique<dae::GameObject>();
    p1HealthDisplayGO->GetTransform()->SetLocalPosition(40.f, 48.f, 0.f);
    p1HealthDisplayGO->AddComponent<dae::TextComponent>("LIVES: 3", dae::GameState::fontArcade);
    p1HealthDisplayGO->AddComponent<dae::HealthDisplay>(health1, health1);
    dae::GameState::scene->Add(std::move(p1HealthDisplayGO));

    auto p2LabelGO = std::make_unique<dae::GameObject>();
    p2LabelGO->GetTransform()->SetLocalPosition(200.f, 20.f, 0.f);
    p2LabelGO->AddComponent<dae::TextComponent>("2UP", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(p2LabelGO));

    auto p2ScoreDisplayGO = std::make_unique<dae::GameObject>();
    p2ScoreDisplayGO->GetTransform()->SetLocalPosition(200.f, 34.f, 0.f);
    p2ScoreDisplayGO->AddComponent<dae::TextComponent>("000000", dae::GameState::fontArcade);
    p2ScoreDisplayGO->AddComponent<dae::ScoreDisplay>(score2, score2);
    dae::GameState::scene->Add(std::move(p2ScoreDisplayGO));

    auto p2HealthDisplayGO = std::make_unique<dae::GameObject>();
    p2HealthDisplayGO->GetTransform()->SetLocalPosition(200.f, 48.f, 0.f);
    p2HealthDisplayGO->AddComponent<dae::TextComponent>("LIVES: 3", dae::GameState::fontArcade);
    p2HealthDisplayGO->AddComponent<dae::HealthDisplay>(health2, health2);
    dae::GameState::scene->Add(std::move(p2HealthDisplayGO));

    auto hiScoreLabelGO = std::make_unique<dae::GameObject>();
    hiScoreLabelGO->GetTransform()->SetLocalPosition(340.f, 20.f, 0.f);
    hiScoreLabelGO->AddComponent<dae::TextComponent>("HI-SCORE", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(hiScoreLabelGO));

    auto hiScoreGO = std::make_unique<dae::GameObject>();
    hiScoreGO->GetTransform()->SetLocalPosition(340.f, 34.f, 0.f);
    s_hiScoreText = hiScoreGO->AddComponent<dae::TextComponent>("000000", dae::GameState::fontArcade);
    dae::GameState::scene->Add(std::move(hiScoreGO));

    auto levelMgrGO = std::make_unique<dae::GameObject>();
    s_levelMgr = levelMgrGO->AddComponent<dae::LevelManagerComponent>();
    dae::SpawnEnemiesFromData(initialSpawns, *dae::GameState::scene, s_levelMgr, s_melonFood, s_friesFood, s_boulderPool);
    s_levelMgr->SetOnLevelComplete(OnLevelComplete);
    dae::GameState::scene->Add(std::move(levelMgrGO));

    dae::GameState::onGameOver = []()
        {
            const int score = s_score1->GetScore();
            dae::SceneManager::GetInstance().RequestTransition([score]()
                {
                    MultiplayerGameState::OnExit();
                    NameEntryState::OnEnter(score);
                });
        };

    auto& input = dae::InputManager::GetInstance();
    input.BindCommand(SDL_SCANCODE_F2, dae::KeyState::Down, std::make_unique<dae::StopSoundCommand>());
    input.BindCommand(SDL_SCANCODE_F1, dae::KeyState::Down, std::make_unique<dae::SkipLevelCommand>(s_levelMgr, OnSkipLevel));
    dae::BindPlayerInputs(input, s_p1, physics1, p1State, dae::GameState::p1Config);
    dae::BindPlayerInputs(input, s_p2, p2Physics, p2State, dae::GameState::p2Config);
}

void MultiplayerGameState::OnExit()
{
    dae::GameState::onGameOver = {};
    dae::ClearGameScene();
    s_p1 = nullptr;
    s_p2 = nullptr;
    s_score1 = nullptr;
    s_levelMgr = nullptr;
    s_melonFood = nullptr;
    s_friesFood = nullptr;
    s_boulderPool = nullptr;
    s_hiScoreText = nullptr;
}