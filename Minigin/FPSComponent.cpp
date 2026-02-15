#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <sstream>
#include <iomanip>

dae::FPSComponent::FPSComponent(GameObject* owner)
    : BaseComponent(owner), m_pTextComponent(nullptr), m_accumulatedTime(0.0f), m_frameCount(0), m_updateInterval(0.5f)
{
    m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
}

void dae::FPSComponent::Update(const float deltaTime)
{
    m_accumulatedTime += deltaTime;
    ++m_frameCount;

    if (m_accumulatedTime >= m_updateInterval)
    {
        const float fps = static_cast<float>(m_frameCount) / m_accumulatedTime;
        //GetOwner()->SendMessage("FPSUpdated", m_fps);

        std::stringstream ss;
        ss << "FPS: " << std::fixed << std::setprecision(1) << fps;

        auto* textComponent = GetOwner()->GetComponent<TextComponent>();
        if (textComponent)
        {
            textComponent->SetText(ss.str());
        }

        m_accumulatedTime = 0.0f;
        m_frameCount = 0;
    }   
}