#pragma once
#include <functional>
#include "Command.h"
#include "GameState.h"
#include "MainMenuComponent.h"
#include "NameEntryComponent.h"

namespace dae
{
	class NameEntryComponent;
    class SelectModeCommand final : public Command
    {
    public:
        SelectModeCommand(MainMenuComponent* menu, GameMode mode, InputDevice device, unsigned int controllerIdx = 0);
        void Execute(float) override;
    private:
        MainMenuComponent* m_menu;
        GameMode m_mode;
        InputDevice m_device;
        unsigned int m_controllerIdx;
    };

    enum class NameEntryAction { ScrollUp, ScrollDown, CursorLeft, CursorRight, Confirm };

    class NameEntryCommand final : public Command
    {
    public:
        NameEntryCommand(NameEntryComponent* target, NameEntryAction action);
        void Execute(float) override;
    private:
        NameEntryComponent* m_target;
        NameEntryAction m_action;
    };

    class LambdaCommand final : public Command
    {
    public:
        explicit LambdaCommand(std::function<void()> fn);
        void Execute(float) override;
    private:
        std::function<void()> m_fn;
    };
}