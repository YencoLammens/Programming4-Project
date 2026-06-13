#include "SkipLevelCommand.h"

namespace dae
{
    SkipLevelCommand::SkipLevelCommand(LevelManagerComponent* levelMgr, std::function<void()> onSkip)
        : m_levelMgr(levelMgr), m_onSkip(std::move(onSkip))
    {
    }

    void SkipLevelCommand::Execute(float)
    {
        if (m_levelMgr) m_levelMgr->ClearAndReset();
        if (m_onSkip) m_onSkip();
    }
}