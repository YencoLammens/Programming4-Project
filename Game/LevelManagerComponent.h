#pragma once
#include <vector>
#include <functional>
#include "BaseComponent.h"

namespace dae
{
    class LevelManagerComponent final : public BaseComponent
    {
    public:
        explicit LevelManagerComponent(GameObject* owner);
        ~LevelManagerComponent() override = default;
        LevelManagerComponent(const LevelManagerComponent&) = delete;
        LevelManagerComponent& operator=(const LevelManagerComponent&) = delete;
        LevelManagerComponent(LevelManagerComponent&&) = delete;
        LevelManagerComponent& operator=(LevelManagerComponent&&) = delete;

        void Update(float deltaTime) override;
        void FixedUpdate(float) override {}

        void RegisterEnemy(GameObject* enemy);
        void SetOnLevelComplete(std::function<void()> callback);

    private:
        std::vector<GameObject*> m_enemies;
        std::function<void()> m_onLevelComplete;
        
        static constexpr float s_transitionDelay{ 2.f };
        float m_transitionTimer{ -1.f };
        bool m_levelComplete{ false };
    };
}