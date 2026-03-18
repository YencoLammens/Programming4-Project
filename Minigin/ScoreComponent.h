#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
    class ScoreComponent final : public BaseComponent, public Subject
    {
    public:
        explicit ScoreComponent(GameObject* owner);
        ~ScoreComponent() override = default;

        ScoreComponent(const ScoreComponent&) = delete;
        ScoreComponent& operator=(const ScoreComponent&) = delete;
        ScoreComponent(ScoreComponent&&) = delete;
        ScoreComponent& operator=(ScoreComponent&&) = delete;

        void Update(const float) override {};
        void FixedUpdate(const float) override {};

        void AddPoints(int points);
        int GetScore() const { return m_score; }

    private:
        int m_score{ 0 };
    };
}