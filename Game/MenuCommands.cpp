#include "MenuCommands.h"
#include "NameEntryComponent.h"

namespace dae
{
    SelectModeCommand::SelectModeCommand(MainMenuComponent* menu, GameMode mode, InputDevice device, unsigned int controllerIdx)
        : m_menu(menu), m_mode(mode), m_device(device), m_controllerIdx(controllerIdx)
    {
    }

    void SelectModeCommand::Execute(float)
    {
        if (m_menu) m_menu->SelectMode(m_mode, m_device, m_controllerIdx);
    }

    NameEntryCommand::NameEntryCommand(NameEntryComponent* target, NameEntryAction action)
        : m_target(target), m_action(action)
    {
    }

    void NameEntryCommand::Execute(float)
    {
        if (!m_target) return;
        switch (m_action)
        {
        case NameEntryAction::ScrollUp: 
            m_target->OnScrollUp(); 
            break;
        case NameEntryAction::ScrollDown: 
            m_target->OnScrollDown(); 
            break;
        case NameEntryAction::CursorLeft: 
            m_target->OnCursorLeft(); 
            break;
        case NameEntryAction::CursorRight: 
            m_target->OnCursorRight(); 
            break;
        case NameEntryAction::Confirm:
            m_target->OnConfirm(); 
            break;
        }
    }

    LambdaCommand::LambdaCommand(std::function<void()> fn)
        : m_fn(std::move(fn))
    {
    }

    void LambdaCommand::Execute(float)
    {
        if (m_fn) m_fn();
    }
}