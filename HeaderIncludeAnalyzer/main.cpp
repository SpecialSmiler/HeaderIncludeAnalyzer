#include "FileSearcher.hpp"
#include "HeaderAnalyzer.hpp"
#include "Printer.hpp"
#include "ImguiIntergrate.hpp"

class ExtensionCollector : public FileCollector
{
public:
    void collect(const fs::path& path) override
    {
        if (fs::is_regular_file(path) && path.has_extension())
            m_extension.insert(path.extension());
    }
    void print()
    {
        PrintSet<fs::path>(m_extension, [](const fs::path& path) -> std::string { return path.u8string(); });
    }
private:
    std::set<fs::path> m_extension;
};

class HeaderFileCollector : public FileCollector
{
public:
    void collect(const fs::path& path) override
    {
        if (fs::is_regular_file(path) && FileSearcher::is_header_extension(path.extension()))
            m_headeFiles.push_back(path);
    }
    void print()
    {
        PrintVector<fs::path>(m_headeFiles, [](const fs::path& path) -> std::string { return path.u8string(); });
    }
private:
    std::vector<fs::path> m_headeFiles;
};

void FileAnalyzeDemo()
{
    FileSearcher fileSearcher("D:\\Programing\\MySQL\\mysql-8.0.28");
    fileSearcher.add_excluded_directory("D:\\Programing\\MySQL\\mysql-8.0.28\\.git");
    fileSearcher.add_excluded_directory("D:\\Programing\\MySQL\\mysql-8.0.28\\boost");
    fileSearcher.add_excluded_directory("D:\\Programing\\MySQL\\mysql-8.0.28\\extra");
    //ExtensionCollector collector;
    HeaderFileCollector collector;
    fileSearcher.search_files(&collector);
    collector.print();

    //HeaderManager headerManager;
    //headerManager.analyze_include("D:\\Programing\\MySQL\\mysql-8.0.28\\client\\client_priv.h");
}

int main()
{
    int err = 0;

    err = ImguiMain();

    return err;
}