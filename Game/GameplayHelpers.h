#pragma once
#include <vector>
#include "GameState.h"
#include "TilemapLoader.h"

namespace dae
{
    class Scene;
    class InputManager;
    class GameObject;
    class PhysicsComponent;
    class PlayerStateController;
    class LevelManagerComponent;
    class FoodPoolComponent;
    class BoulderPoolComponent;

    void ClearGameScene();

    void SpawnEnemiesFromData(const std::vector<EnemySpawnData>& spawns, Scene& scene, LevelManagerComponent* mgr, FoodPoolComponent* melonFood, FoodPoolComponent* friesFood, BoulderPoolComponent* boulderPool);

    void BindPlayerInputs(InputManager& input, GameObject* player, PhysicsComponent* physics, PlayerStateController* state, const PlayerInputConfig& config);
}