#include "FileSearcher.hpp"
#include "HeaderAnalyzer.hpp"
#include "Printer.hpp"

void GetAndPrintAllExtension(const FileSearcher& analyzer)
{
    std::set<fs::path> allExtensions;

    analyzer.search_files([&allExtensions](const fs::path& path)
        {
            if (fs::is_regular_file(path) && path.has_extension())
                allExtensions.insert(path.extension());
        }
    );
    PrintSet<fs::path>(allExtensions,[](const fs::path& path) -> std::string { return path.u8string();});
}

void GetAndPrintAllHeaderFiles(const FileSearcher& analyzer)
{
    std::vector<fs::path> headerFiles;
    analyzer.search_files([&headerFiles](const fs::path& path) {
        if (fs::is_regular_file(path) && FileSearcher::is_header_extension(path.extension()))
        {
            headerFiles.push_back(path);
        }
    });
    PrintVector<fs::path>(headerFiles, [](const fs::path& path) -> std::string { return path.u8string(); });
}

int main()
{
    //FileSearcher fileSearcher("D:\\Programing\\MySQL\\mysql-8.0.28");
    //fileSearcher.add_excluded_directory("D:\\Programing\\MySQL\\mysql-8.0.28\\.git");
    //fileSearcher.add_excluded_directory("D:\\Programing\\MySQL\\mysql-8.0.28\\boost");
    //fileSearcher.add_excluded_directory("D:\\Programing\\MySQL\\mysql-8.0.28\\extra");
    //GetAndPrintAllHeaderFiles(fileSearcher);

    HeaderManager headerManager;
    headerManager.analyze_include("D:\\Programing\\MySQL\\mysql-8.0.28\\client\\client_priv.h");

    return 0;
}