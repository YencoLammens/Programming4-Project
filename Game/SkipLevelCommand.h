#pragma once
#include <functional>
#include "Command.h"
#include "LevelManagerComponent.h"

namespace dae
{
    class SkipLevelCommand final : public Command
    {
    public:
        SkipLevelCommand(LevelManagerComponent* levelMgr, std::function<void()> onSkip);
        void Execute(float) override;
    private:
        LevelManagerComponent* m_levelMgr;
        std::function<void()> m_onSkip;
    };
}