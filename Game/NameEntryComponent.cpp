#include "NameEntryComponent.h"
#include "TextComponent.h"

namespace dae
{
    NameEntryComponent::NameEntryComponent(GameObject* owner, TextComponent* display, OnConfirmedFn onConfirmed)
        : BaseComponent(owner), m_display(display), m_onConfirmed(std::move(onConfirmed))
    {
        RefreshDisplay();
    }

    void NameEntryComponent::OnScrollUp()
    {
        if (m_confirmed) return;
        m_charIndices[m_cursorPos] = (m_charIndices[m_cursorPos] + 1) % k_numChars;
        RefreshDisplay();
    }

    void NameEntryComponent::OnScrollDown()
    {
        if (m_confirmed) return;
        m_charIndices[m_cursorPos] = (m_charIndices[m_cursorPos] - 1 + k_numChars) % k_numChars;
        RefreshDisplay();
    }

    void NameEntryComponent::OnCursorLeft()
    {
        if (m_confirmed) return;
        if (m_cursorPos > 0) --m_cursorPos;
        RefreshDisplay();
    }

    void NameEntryComponent::OnCursorRight()
    {
        if (m_confirmed) return;
        if (m_cursorPos < k_slots - 1) ++m_cursorPos;
        RefreshDisplay();
    }

    void NameEntryComponent::OnConfirm()
    {
        if (m_confirmed) return;
        m_confirmed = true;

        std::string name;
        for (int i = 0; i < k_slots; ++i)
            name += (m_charIndices[i] < 26) ? static_cast<char>('A' + m_charIndices[i]) : ' ';

        if (m_onConfirmed)
            m_onConfirmed(name);
    }

    void NameEntryComponent::RefreshDisplay()
    {
        if (!m_display) return;
        std::string text;
        for (int i = 0; i < k_slots; ++i)
        {
            if (i == m_cursorPos) text += '[';
            text += (m_charIndices[i] < 26) ? static_cast<char>('A' + m_charIndices[i]) : ' ';
            if (i == m_cursorPos) text += ']';
            if (i < k_slots - 1) text += "   ";
        }
        m_display->SetText(text);
    }
}