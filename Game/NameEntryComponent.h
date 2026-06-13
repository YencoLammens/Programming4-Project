#pragma once
#include <array>
#include <functional>
#include <string>
#include "BaseComponent.h"

namespace dae
{
    class TextComponent;

    class NameEntryComponent final : public BaseComponent
    {
    public:
        using OnConfirmedFn = std::function<void(const std::string&)>;

        NameEntryComponent(GameObject* owner, TextComponent* display, OnConfirmedFn onConfirmed);
        ~NameEntryComponent() override = default;
        NameEntryComponent(const NameEntryComponent&) = delete;
        NameEntryComponent& operator=(const NameEntryComponent&) = delete;
        NameEntryComponent(NameEntryComponent&&) = delete;
        NameEntryComponent& operator=(NameEntryComponent&&) = delete;

        void Update(float) override {}
        void FixedUpdate(float) override {}

        void OnScrollUp();
        void OnScrollDown();
        void OnCursorLeft();
        void OnCursorRight();
        void OnConfirm();

    private:
        void RefreshDisplay();

        static constexpr int k_numChars{ 27 };
        static constexpr int k_slots{ 3 };

        TextComponent* m_display;
        OnConfirmedFn m_onConfirmed;
        std::array<int, k_slots> m_charIndices{ 0, 0, 0 };
        int m_cursorPos{ 0 };
        bool m_confirmed{ false };
    };
}