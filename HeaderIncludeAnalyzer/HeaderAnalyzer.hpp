#pragma once
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class Header
{
    enum class Type
    {
        Internal, // belongs to this project
        External, // belongs 3rd library
    };

public:
    Header() = default;
    Header(const fs::path& path, const std::vector<Header*> includeHeaders)
        :m_path(path), m_includeHeaders(includeHeaders)
    {}

private:
    Type m_type = Type::Internal;
    fs::path m_path;
    std::vector<Header*> m_includeHeaders;
};


class HeaderManager
{
public:
    Header* get_header(const fs::path& path);

    void analyze_include(const fs::path& filePath);
private:

private:
    std::vector<std::unique_ptr<Header>> m_headers;
};
