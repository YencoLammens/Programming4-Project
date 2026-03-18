#include "SteamAchievementComponent.h"
#include "ScoreComponent.h"

#ifdef USE_STEAMWORKS
#pragma warning(push)
#pragma warning(disable:4996)
#include <steam_api.h>
#pragma warning(pop)

namespace dae
{
    SteamAchievementComponent::SteamAchievementComponent(GameObject* owner, Subject* subject, ScoreComponent* scoreComponent)
        : BaseComponent(owner), Observer(subject), m_scoreComponent(scoreComponent)
    {
    }

    void SteamAchievementComponent::Notify(EventId event)
    {
        if (event == make_sdbm_hash("PointsGained"))
        {
            if (m_scoreComponent && m_scoreComponent->GetScore() >= 500)
            {
                ISteamUserStats* stats = SteamUserStats();
                if (stats)
                {
                    stats->SetAchievement("ACH_WIN_ONE_GAME");
                    stats->StoreStats();
                }
            }
        }
    }
}
#endif