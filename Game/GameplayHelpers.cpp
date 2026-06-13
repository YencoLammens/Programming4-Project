#include "GameplayHelpers.h"
#include "GameState.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "PlayerStateController.h"
#include "LevelManagerComponent.h"
#include "FoodPoolComponent.h"
#include "BoulderPoolComponent.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "HitboxComponent.h"
#include "AnimationComponent.h"
#include "FacingComponent.h"
#include "MaitaShootComponent.h"
#include "ZenChanStateController.h"
#include "MaitaStateController.h"
#include "EnemyBubbledObserver.h"
#include "WanderingState.h"
#include "CollisionLayer.h"
#include "MoveCommand.h"
#include "JumpCommand.h"
#include "ShootBubbleCommand.h"
#include "Controller.h"
#include "Renderer.h"
#include "EventId.h"
#include <SDL3/SDL.h>
#include <glm/glm.hpp>

namespace dae
{
    void ClearGameScene()
    {
        TilemapLoader::ClearLoadedTiles();
        GameState::scene->RemoveAll();
        InputManager::GetInstance().ClearAllBindings();
        Renderer::GetInstance().SetCameraOffset({ 0.f, 0.f });
        Renderer::GetInstance().ClearCameraClipRect();
    }

    void SpawnEnemiesFromData(const std::vector<EnemySpawnData>& spawns, Scene& scene, LevelManagerComponent* mgr, FoodPoolComponent* melonFood, FoodPoolComponent* friesFood, BoulderPoolComponent* boulderPool)
    {
        for (const auto& spawn : spawns)
        {
            auto enemy = std::make_unique<GameObject>();
            auto* enemyRender = enemy->AddComponent<RenderComponent>();
            enemy->GetTransform()->SetLocalPosition(spawn.x, spawn.y, 0.f);
            auto* enemyHitbox = enemy->AddComponent<HitboxComponent>(14.f, 14.f);
            enemyHitbox->SetLayer(CollisionLayer::Enemy);
            enemy->AddComponent<PhysicsComponent>();
            enemy->AddComponent<FacingComponent>();
            auto* enemyAnim = enemy->AddComponent<AnimationComponent>(enemyRender);

            if (spawn.type == "ZenChan")
            {
                enemyRender->SetTexture(ResourceManager::GetInstance().LoadTexture("ZenchanWalking.png"));
                enemyAnim->AddClip(make_sdbm_hash("walk"), AnimationClip{ ResourceManager::GetInstance().LoadTexture("ZenchanWalking.png"), 2, 16, 16, 0.15f });
                enemyAnim->AddClip(make_sdbm_hash("bubbled"), AnimationClip{ ResourceManager::GetInstance().LoadTexture("ZenchanBubbled.png"), 1, 16, 16, 0.2f });
                enemyAnim->AddClip(make_sdbm_hash("popped"), AnimationClip{ ResourceManager::GetInstance().LoadTexture("ZenchanPopped.png"), 4, 16, 16, 0.1f });
                enemyAnim->Play(make_sdbm_hash("walk"));
                auto* enemyState = enemy->AddComponent<ZenChanStateController>(std::make_unique<WanderingState>(), melonFood);
                enemy->AddComponent<EnemyBubbledObserver>(enemyHitbox, enemyState);
            }
            else if (spawn.type == "Maita")
            {
                enemyRender->SetTexture(ResourceManager::GetInstance().LoadTexture("MaitaWalking.png"));
                enemyAnim->AddClip(make_sdbm_hash("walk"), AnimationClip{ ResourceManager::GetInstance().LoadTexture("MaitaWalking.png"), 2, 16, 16, 0.15f });
                enemyAnim->AddClip(make_sdbm_hash("bubbled"), AnimationClip{ ResourceManager::GetInstance().LoadTexture("MaitaBubbled.png"), 1, 16, 16, 0.2f });
                enemyAnim->AddClip(make_sdbm_hash("popped"), AnimationClip{ ResourceManager::GetInstance().LoadTexture("MaitaPopped.png"), 4, 16, 16, 0.1f });
                enemyAnim->Play(make_sdbm_hash("walk"));
                auto* facing = enemy->GetComponent<FacingComponent>();
                auto* shoot = enemy->AddComponent<MaitaShootComponent>(boulderPool, facing);
                auto* enemyState = enemy->AddComponent<MaitaStateController>(std::make_unique<WanderingState>(), friesFood, shoot);
                enemy->AddComponent<EnemyBubbledObserver>(enemyHitbox, enemyState);
            }
            else continue;

            mgr->RegisterEnemy(enemy.get());
            scene.Add(std::move(enemy));
        }
    }

    void BindPlayerInputs(InputManager& input, GameObject* player,  PhysicsComponent* physics, PlayerStateController* state, const PlayerInputConfig& config)
    {
        if (config.device == InputDevice::Keyboard)
        {
            input.BindCommand(SDL_SCANCODE_W, KeyState::Down, std::make_unique<JumpCommand>(player, physics, state));
            input.BindCommand(SDL_SCANCODE_A, KeyState::Pressed, std::make_unique<MoveCommand>(player, glm::vec3{ -1, 0, 0 }, 100.f, state));
            input.BindCommand(SDL_SCANCODE_D, KeyState::Pressed, std::make_unique<MoveCommand>(player, glm::vec3{ 1, 0, 0 }, 100.f, state));
            input.BindCommand(SDL_SCANCODE_SPACE, KeyState::Down, std::make_unique<ShootBubbleCommand>(player, state));
        }
        else
        {
            const unsigned int idx = config.controllerIndex;
            input.BindCommand(idx, Controller::ControllerButton::DPadUp, KeyState::Down, std::make_unique<JumpCommand>(player, physics, state));
            input.BindCommand(idx, Controller::ControllerButton::DPadLeft, KeyState::Pressed, std::make_unique<MoveCommand>(player, glm::vec3{ -1, 0, 0 }, 100.f, state));
            input.BindCommand(idx, Controller::ControllerButton::DPadRight, KeyState::Pressed, std::make_unique<MoveCommand>(player, glm::vec3{ 1, 0, 0 }, 100.f, state));
            input.BindCommand(idx, Controller::ControllerButton::ButtonX, KeyState::Down, std::make_unique<ShootBubbleCommand>(player, state));
        }
    }
}