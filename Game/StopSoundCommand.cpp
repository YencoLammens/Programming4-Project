#include "StopSoundCommand.h"
#include "ServiceLocator.h"

void dae::StopSoundCommand::Execute(float)
{
    ServiceLocator::GetSoundSystem().ToggleMute();
}
