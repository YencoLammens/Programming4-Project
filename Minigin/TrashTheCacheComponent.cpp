#include "TrashTheCacheComponent.h"

#include <algorithm>
#include <chrono>
#include <numeric>
#include <vector>

#include <imgui.h>

// ---------------------------------------------------------------------------
//  Structs exactly as defined in the slides
// ---------------------------------------------------------------------------
namespace
{
    struct Transform
    {
        float matrix[16] =
        {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
        };
    };

    class GameObject3D
    {
    public:
        Transform transform{};
        int ID{};
    };

    // Alt version: Transform behind a pointer so the hot loop only touches ID
    class GameObject3DAlt
    {
    public:
        Transform* transform{ nullptr };
        int ID{};
    };

    // ---------------------------------------------------------------------------
    //  Runs numSamples passes over arr with the given stride, removes the single
    //  highest and lowest timing, then returns the average in microseconds.
    // ---------------------------------------------------------------------------
    template<typename T, typename Fn>
    float TimedStep(T* arr, int count, int stride, int numSamples, Fn op)
    {
        std::vector<long long> samples;
        samples.reserve(numSamples);

        for (int s = 0; s < numSamples; ++s)
        {
            const auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < count; i += stride)
                op(arr[i]);
            const auto end = std::chrono::high_resolution_clock::now();
            samples.push_back(
                std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
        }

        if (static_cast<int>(samples.size()) > 2)
        {
            std::sort(samples.begin(), samples.end());
            samples.erase(samples.begin());
            samples.erase(samples.end() - 1);
        }

        const long long sum = std::accumulate(samples.begin(), samples.end(), 0LL);
        return static_cast<float>(sum) / static_cast<float>(samples.size());
    }

    // ---------------------------------------------------------------------------
    //  Draws a PlotLines graph + data table for a timing vector
    // ---------------------------------------------------------------------------
    void DrawPlot(const char* plotId, const char* tableId, const std::vector<float>& timings)
    {
        static const char* labels[] =
        { "1","2","4","8","16","32","64","128","256","512","1024" };

        const int count = static_cast<int>(timings.size());
        const float maxVal = *std::max_element(timings.begin(), timings.end());

        ImGui::PlotLines(plotId,
            timings.data(), count,
            0, nullptr,
            0.0f, maxVal * 1.1f,
            ImVec2(0.f, 140.f));

        if (ImGui::BeginTable(tableId, 2,
            ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit))
        {
            ImGui::TableSetupColumn("Step size");
            ImGui::TableSetupColumn("avg (µs)");
            ImGui::TableHeadersRow();
            for (int i = 0; i < count && i < 11; ++i)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted(labels[i]);
                ImGui::TableSetColumnIndex(1); ImGui::Text("%.1f", timings[i]);
            }
            ImGui::EndTable();
        }
    }

    constexpr int INT_ARRAY_SIZE = 1 << 26;  // 2^26 as per the slides
    constexpr int GO_ARRAY_SIZE = 1 << 22;  // smaller so it stays manageable

} // anonymous namespace

// ---------------------------------------------------------------------------

dae::TrashTheCacheComponent::TrashTheCacheComponent(GameObject* owner)
    : BaseComponent(owner)
{
}

void dae::TrashTheCacheComponent::Update(float) {}
void dae::TrashTheCacheComponent::FixedUpdate(float) {}

// ---------------------------------------------------------------------------
void dae::TrashTheCacheComponent::Render() const
{
    // -----------------------------------------------------------------------
    //  Exercise 1 – integer array
    // -----------------------------------------------------------------------
    ImGui::Begin("Exercise 1");

    ImGui::InputInt("# samples", &m_samplesEx1);
    if (m_samplesEx1 < 1) m_samplesEx1 = 1;

    if (m_measuringEx1)
    {
        ImGui::Text("Measuring... please wait");
    }
    else
    {
        if (ImGui::Button("Trash the cache"))
        {
            m_measuringEx1 = true;
            m_timingsEx1 = MeasureIntegers(m_samplesEx1);
            m_measuringEx1 = false;
        }
    }

    if (!m_timingsEx1.empty())
        DrawPlot("##ex1plot", "##ex1table", m_timingsEx1);

    ImGui::End();

    // -----------------------------------------------------------------------
    //  Exercise 2 – GameObject3D vs GameObject3DAlt
    // -----------------------------------------------------------------------
    ImGui::Begin("Exercise 2");

    ImGui::InputInt("# samples", &m_samplesEx2);
    if (m_samplesEx2 < 1) m_samplesEx2 = 1;

    if (m_measuringEx2)
    {
        ImGui::Text("Measuring... please wait");
    }
    else
    {
        if (ImGui::Button("Thrash the cache with GameObject3D"))
        {
            m_measuringEx2 = true;
            m_timingsGO3D = MeasureGameObject3D(m_samplesEx2);
            m_measuringEx2 = false;
        }

        if (ImGui::Button("Thrash the cache with GameObject3DAlt"))
        {
            m_measuringEx2 = true;
            m_timingsGO3DAlt = MeasureGameObject3DAlt(m_samplesEx2);
            m_measuringEx2 = false;
        }
    }

    if (!m_timingsGO3D.empty())
    {
        ImGui::Text("GameObject3D:");
        DrawPlot("##go3dplot", "##go3dtable", m_timingsGO3D);
    }

    if (!m_timingsGO3DAlt.empty())
    {
        ImGui::Text("GameObject3DAlt:");
        DrawPlot("##go3daltplot", "##go3dalttable", m_timingsGO3DAlt);
    }

    // Combined overlay once both datasets exist (Exercise 3)
    if (!m_timingsGO3D.empty() && !m_timingsGO3DAlt.empty())
    {
        ImGui::Separator();
        ImGui::Text("Combined:");

        const float maxVal = std::max(
            *std::max_element(m_timingsGO3D.begin(), m_timingsGO3D.end()),
            *std::max_element(m_timingsGO3DAlt.begin(), m_timingsGO3DAlt.end()));
        const int count = static_cast<int>(m_timingsGO3D.size());

        ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.2f, 0.6f, 1.0f, 1.0f));
        ImGui::PlotLines("##cmp_go3d",
            m_timingsGO3D.data(), count, 0, "GameObject3D",
            0.0f, maxVal * 1.1f, ImVec2(0.f, 140.f));
        ImGui::PopStyleColor();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 140.f - ImGui::GetStyle().ItemSpacing.y);

        ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.2f, 1.0f, 0.4f, 1.0f));
        ImGui::PlotLines("##cmp_go3dalt",
            m_timingsGO3DAlt.data(), count, 0, "GameObject3DAlt",
            0.0f, maxVal * 1.1f, ImVec2(0.f, 140.f));
        ImGui::PopStyleColor();

        ImGui::TextColored(ImVec4(0.2f, 0.6f, 1.0f, 1.0f), "Blue  = GameObject3D");
        ImGui::SameLine(0.f, 20.f);
        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.4f, 1.0f), "Green = GameObject3DAlt");
    }

    ImGui::End();
}

// ---------------------------------------------------------------------------
//  Exercise 1
// ---------------------------------------------------------------------------
std::vector<float> dae::TrashTheCacheComponent::MeasureIntegers(int numSamples)
{
    std::vector<int> arr(INT_ARRAY_SIZE, 1);
    std::vector<float> results;
    results.reserve(11);

    for (int step = 1; step <= 1024; step *= 2)
        results.push_back(TimedStep(arr.data(), INT_ARRAY_SIZE, step, numSamples,
            [](int& v) { v *= 2; }));

    return results;
}

// ---------------------------------------------------------------------------
//  Exercise 2
// ---------------------------------------------------------------------------
std::vector<float> dae::TrashTheCacheComponent::MeasureGameObject3D(int numSamples)
{
    std::vector<GameObject3D> arr(GO_ARRAY_SIZE);
    for (int i = 0; i < GO_ARRAY_SIZE; ++i) arr[i].ID = i;

    std::vector<float> results;
    results.reserve(11);

    for (int step = 1; step <= 1024; step *= 2)
        results.push_back(TimedStep(arr.data(), GO_ARRAY_SIZE, step, numSamples,
            [](GameObject3D& go) { go.ID *= 2; }));

    return results;
}

// ---------------------------------------------------------------------------
//  Exercise 2 Alt
// ---------------------------------------------------------------------------
std::vector<float> dae::TrashTheCacheComponent::MeasureGameObject3DAlt(int numSamples)
{
    std::vector<Transform> transforms(GO_ARRAY_SIZE);
    std::vector<GameObject3DAlt> arr(GO_ARRAY_SIZE);
    for (int i = 0; i < GO_ARRAY_SIZE; ++i)
    {
        arr[i].ID = i;
        arr[i].transform = &transforms[i];
    }

    std::vector<float> results;
    results.reserve(11);

    for (int step = 1; step <= 1024; step *= 2)
        results.push_back(TimedStep(arr.data(), GO_ARRAY_SIZE, step, numSamples,
            [](GameObject3DAlt& go) { go.ID *= 2; }));

    return results;
}