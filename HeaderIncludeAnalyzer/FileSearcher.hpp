#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <set>
#include <functional>

namespace fs = std::filesystem;

class FileCollector
{
public:
    virtual void collect(const fs::path& path) = 0;
};

class FileSearcher
{
public:
    FileSearcher(const fs::path& directory);

    void search_files(FileCollector* collector) const;

    void add_excluded_directory(const fs::path& directory);

    static bool is_header_extension(const fs::path& extension);

private:
    bool is_excluded_directory(const fs::path& directory) const;

private:
    fs::path m_directory;
    std::set<fs::path> m_excludedDirectories;
};