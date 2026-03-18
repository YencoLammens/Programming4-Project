#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "EventId.h"

namespace dae
{
    class ScoreComponent;

    class SteamAchievementComponent final : public BaseComponent, public Observer
    {
    public:
        SteamAchievementComponent(GameObject* owner, Subject* subject, ScoreComponent* scoreComponent);
        ~SteamAchievementComponent() override = default;

        SteamAchievementComponent(const SteamAchievementComponent&) = delete;
        SteamAchievementComponent& operator=(const SteamAchievementComponent&) = delete;
        SteamAchievementComponent(SteamAchievementComponent&&) = delete;
        SteamAchievementComponent& operator=(SteamAchievementComponent&&) = delete;

        void Update(const float) override {}
        void FixedUpdate(const float) override {}

        void Notify(EventId event) override;

    private:
        void UnlockAchievement(const char* achievementId);
        ScoreComponent* m_scoreComponent{ nullptr };
    };
}