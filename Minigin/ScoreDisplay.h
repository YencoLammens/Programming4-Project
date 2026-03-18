#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
    class TextComponent;
    class ScoreComponent;

    class ScoreDisplay final : public BaseComponent, public Observer
    {
    public:
        ScoreDisplay(GameObject* owner, Subject* subject, ScoreComponent* scoreComponent);
        ~ScoreDisplay() override = default;

        ScoreDisplay(const ScoreDisplay&) = delete;
        ScoreDisplay& operator=(const ScoreDisplay&) = delete;
        ScoreDisplay(ScoreDisplay&&) = delete;
        ScoreDisplay& operator=(ScoreDisplay&&) = delete;

        void Update(const float) override {};
        void FixedUpdate(const float) override {};

        void Notify(EventId event) override;

    private:
        TextComponent* m_textComponent{ nullptr };
        ScoreComponent* m_scoreComponent{ nullptr };
    };
}