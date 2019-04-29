#include "json/writer.hpp"
#include <fstream>

bool fileWriter(std::string path, std::string content)
{
    return fileWriter(path.c_str(), content);
}

bool fileWriter(const char* path, std::string content)
{
    std::ofstream file(path, std::ios::out | std::ios::trunc);

    if (!file.is_open()) return false;

    file << content;
    file.close();

    return file.good();
}