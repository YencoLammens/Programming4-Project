#pragma once
#include "Command.h"

namespace dae
{
    class StopSoundCommand final : public Command
    {
    public:
        StopSoundCommand() = default;
        void Execute(float deltaTime) override;
    };
}