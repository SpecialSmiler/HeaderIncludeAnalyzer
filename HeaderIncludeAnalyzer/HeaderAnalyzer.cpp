#include "HeaderAnalyzer.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include "Printer.hpp"


Header* HeaderManager::get_header(const fs::path& path)
{
    //auto it = std::find(m_headers.begin(), m_headers.end(),
    //    [] (const std::unique_ptr<Header>& item){
    //        return false;
    //    });

    return nullptr;
}

void HeaderManager::analyze_include(const fs::path& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return;
    }

    std::vector<std::string> result;

    std::string line;
    std::regex includePattern(R"(\s*#include\s+[<"]([^">]+)[">])");
    while (std::getline(file, line))
    {
        std::smatch match;
        if (std::regex_match(line, match, includePattern))
        {
            result.push_back(match[1].str());
        }
    }

    PrintVector<std::string>(result, nullptr);
}
