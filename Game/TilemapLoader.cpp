#include "TilemapLoader.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "HitboxComponent.h"
#include "CollisionLayer.h"
#include "ResourceManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <SDL3/SDL.h>

namespace dae
{
    std::vector<EnemySpawnData> TilemapLoader::Load(Scene& scene, const std::string& filePath)
    {
        for (auto* tile : s_loadedTiles)
            tile->MarkForDeletion();
        s_loadedTiles.clear();

        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("TilemapLoader: could not open " + filePath);

        const auto mapData = nlohmann::json::parse(file);

        const int mapWidth = mapData["width"];
        const int tileWidth = mapData["tilewidth"];
        const int tileHeight = mapData["tileheight"];

        const auto& tilesetData = mapData["tilesets"][0];
        const int firstGid = tilesetData["firstgid"];
        const int columns = tilesetData["columns"];
        const std::string rawImagePath = tilesetData["image"];
        const std::string textureName = std::filesystem::path(rawImagePath).filename().string();

        auto* tilesetTexture = ResourceManager::GetInstance().LoadTexture(textureName);

        for (const auto& layer : mapData["layers"])
        {
            if (layer["type"] != "tilelayer") continue;

            CollisionLayer tileLayer = CollisionLayer::None;
            if (layer["name"] == "Platforms") tileLayer = CollisionLayer::Platform;
            else if (layer["name"] == "Walls") tileLayer = CollisionLayer::Wall;

            const auto& data = layer["data"];
            for (int i = 0; i < static_cast<int>(data.size()); ++i)
            {
                const int tileId = data[i];
                if (tileId == 0) continue;

                const int tileIndex = tileId - firstGid;
                const int srcCol = tileIndex % columns;
                const int srcRow = tileIndex / columns;

                const SDL_FRect srcRect{
                    static_cast<float>(srcCol * tileWidth),
                    static_cast<float>(srcRow * tileHeight),
                    static_cast<float>(tileWidth),
                    static_cast<float>(tileHeight)
                };

                const float worldX = static_cast<float>((i % mapWidth) * tileWidth);
                const float worldY = static_cast<float>((i / mapWidth) * tileHeight);

                auto go = std::make_unique<GameObject>();
                go->GetTransform()->SetLocalPosition(worldX, worldY, 0.f);

                auto* render = go->AddComponent<RenderComponent>();
                render->SetTexture(tilesetTexture);
                render->SetSourceRect(srcRect);

                if (tileLayer != CollisionLayer::None)
                {
                    auto* hb = go->AddComponent<HitboxComponent>(
                        static_cast<float>(tileWidth),
                        static_cast<float>(tileHeight)
                    );
                    hb->SetLayer(tileLayer);
                }

                s_loadedTiles.push_back(go.get());
                scene.Add(std::move(go));
            }
        }

        std::vector<EnemySpawnData> spawns;
        for (const auto& layer : mapData["layers"])
        {
            if (layer["type"] != "objectgroup") continue;
            const auto layerClass = layer.value("class", std::string{});
            if (layerClass.empty()) continue;
            for (const auto& obj : layer["objects"])
            {
                spawns.push_back({ obj["x"].get<float>(), obj["y"].get<float>(), layerClass});
            }
        }
        return spawns;
    }
}