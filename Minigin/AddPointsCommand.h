#pragma once
#include "Command.h"
#include "ScoreComponent.h"

namespace dae
{
    class AddPointsCommand final : public GameObjectCommand
    {
    public:
        AddPointsCommand(GameObject* gameObject, ScoreComponent* scoreComponent, int points);
        ~AddPointsCommand() override = default;

        AddPointsCommand(const AddPointsCommand&) = delete;
        AddPointsCommand& operator=(const AddPointsCommand&) = delete;
        AddPointsCommand(AddPointsCommand&&) = delete;
        AddPointsCommand& operator=(AddPointsCommand&&) = delete;

        void Execute(float) override;

    private:
        ScoreComponent* m_scoreComponent;
        int m_points;
    };
}