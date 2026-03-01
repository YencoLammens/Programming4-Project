#pragma once
#include <vector>
#include "BaseComponent.h"

namespace dae
{
    class TrashTheCacheComponent final : public BaseComponent
    {
    public:
        explicit TrashTheCacheComponent(GameObject* owner);
        ~TrashTheCacheComponent() override = default;

        TrashTheCacheComponent(const TrashTheCacheComponent&) = delete;
        TrashTheCacheComponent& operator=(const TrashTheCacheComponent&) = delete;
        TrashTheCacheComponent(TrashTheCacheComponent&&) = delete;
        TrashTheCacheComponent& operator=(TrashTheCacheComponent&&) = delete;

        void Update(float deltaTime)      override;
        void FixedUpdate(float fixedStep) override;
        void Render()                     const override;

    private:
        static std::vector<float> MeasureIntegers(int numSamples);
        static std::vector<float> MeasureGameObject3D(int numSamples);
        static std::vector<float> MeasureGameObject3DAlt(int numSamples);

        // Exercise 1
        mutable int  m_samplesEx1{ 10 };
        mutable bool m_measuringEx1{ false };
        mutable std::vector<float> m_timingsEx1;

        // Exercise 2
        mutable int  m_samplesEx2{ 10 };
        mutable bool m_measuringEx2{ false };
        mutable std::vector<float> m_timingsGO3D;
        mutable std::vector<float> m_timingsGO3DAlt;
    };
}