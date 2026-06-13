#pragma once
#include <string>
#include <vector>

namespace dae
{
    struct HighScoreEntry
    {
        std::string name;
        int score;
    };

    class HighScoreManager final
    {
    public:
        HighScoreManager() = delete;
        static std::vector<HighScoreEntry> Load(const std::string& filePath);
        static void Save(const std::string& filePath, const std::vector<HighScoreEntry>& entries);
        static void Insert(const std::string& filePath, const HighScoreEntry& entry, int maxEntries = 10);
    };
}