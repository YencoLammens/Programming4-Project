#include "HighScoreManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
#include <stdexcept>

namespace dae
{
    std::vector<HighScoreEntry> HighScoreManager::Load(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
            return {};
        try
        {
            auto data = nlohmann::json::parse(file);
            std::vector<HighScoreEntry> entries;
            entries.reserve(data.size());
            for (const auto& e : data)
                entries.push_back({ e["name"].get<std::string>(), e["score"].get<int>() });
            return entries;
        }
        catch (...)
        {
            return {};
        }
    }

    void HighScoreManager::Save(const std::string& filePath, const std::vector<HighScoreEntry>& entries)
    {
        nlohmann::json data = nlohmann::json::array();
        for (const auto& e : entries)
            data.push_back({ {"name", e.name}, {"score", e.score} });

        std::ofstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("HighScoreManager: could not write to " + filePath);
        file << data.dump(4);
    }

    void HighScoreManager::Insert(const std::string& filePath, const HighScoreEntry& entry, int maxEntries)
    {
        auto entries = Load(filePath);
        entries.push_back(entry);
        std::sort(entries.begin(), entries.end(),
            [](const HighScoreEntry& a, const HighScoreEntry& b) { return a.score > b.score; });
        if (static_cast<int>(entries.size()) > maxEntries)
            entries.resize(static_cast<size_t>(maxEntries));
        Save(filePath, entries);
    }
}