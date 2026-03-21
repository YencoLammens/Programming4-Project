#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
    class TextComponent;
    class ScoreComponent;
    class Subject;

    class ScoreDisplay final : public BaseComponent, public Observer
    {
    public:
        ScoreDisplay(GameObject* owner, Subject* subject, ScoreComponent* scoreComponent);
        ~ScoreDisplay() override;

        ScoreDisplay(const ScoreDisplay&) = delete;
        ScoreDisplay& operator=(const ScoreDisplay&) = delete;
        ScoreDisplay(ScoreDisplay&&) = delete;
        ScoreDisplay& operator=(ScoreDisplay&&) = delete;

        void Update(const float) override {}
        void FixedUpdate(const float) override {}

        void Notify(EventId event) override;
        void OnSubjectDestroyed() override { m_subject = nullptr; }

    private:
        TextComponent* m_textComponent{ nullptr };
        ScoreComponent* m_scoreComponent{ nullptr };
        Subject* m_subject{ nullptr };
    };
}