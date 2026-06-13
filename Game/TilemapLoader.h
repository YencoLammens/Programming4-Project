#pragma once
#include <string>
#include <vector>

namespace dae
{
    class Scene;
    class GameObject;

    struct EnemySpawnData
    {
        float x;
        float y;
        std::string type;
    };

    class TilemapLoader final
    {
    public:
        TilemapLoader() = delete;
        static std::vector<EnemySpawnData> Load(Scene& scene, const std::string& filePath);
        static void ClearLoadedTiles() { s_loadedTiles.clear(); }

    private:
        static inline std::vector<GameObject*> s_loadedTiles;
    };
}