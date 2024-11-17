#pragma once
#include <vector>
#include <set>
#include <functional>

template <typename T>
void PrintVector(const std::vector<T>& vec, std::function<std::string(const T& item)> printer)
{
    if (printer)
    {
        for (const T& item : vec)
            std::cout << printer(item) << std::endl;
    }
    else
    {
        for (const T& item : vec)
            std::cout << item << std::endl;
    }
}

template <typename T>
void PrintSet(const std::set<T>& set, std::function<std::string(const T& item)> printer)
{
    if (printer)
    {
        for (const T& item : set)
            std::cout << printer(item) << std::endl;
    }
    else
    {
        for (const T& item : set)
            std::cout << item << std::endl;
    }
}