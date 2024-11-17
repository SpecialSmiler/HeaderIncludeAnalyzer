#include "FileSearcher.hpp"

FileSearcher::FileSearcher(const fs::path& directory)
    : m_directory(directory)
{
}

void FileSearcher::search_files(SearchCallback callback) const
{
    if (m_directory.empty())
        return;

    try {
        for (auto it = fs::recursive_directory_iterator(m_directory); it != fs::end(it); ++it)
        {
            if (it->is_directory() && is_excluded_directory(it->path()))
            {
                it.disable_recursion_pending();
                continue;
            }
            callback(it->path());
        }

    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void FileSearcher::add_excluded_directory(const fs::path& directory)
{
    m_excludedDirectories.insert(directory);
}

bool FileSearcher::is_header_extension(const fs::path& extension)
{
    static std::vector<fs::path> headerExtensions = { ".h", ".hpp", ".hh" };
    return std::find(headerExtensions.begin(), headerExtensions.end(), extension) != headerExtensions.end();
}

bool FileSearcher::is_excluded_directory(const fs::path & directory) const
{
    return std::find(m_excludedDirectories.begin(), m_excludedDirectories.end(), directory) != m_excludedDirectories.end();
}
