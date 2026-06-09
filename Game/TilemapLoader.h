#pragma once
#include <string>

namespace dae
{
    class Scene;

    class TilemapLoader final
    {
    public:
        TilemapLoader() = delete;
        static void Load(Scene& scene, const std::string& filePath);
    };
}