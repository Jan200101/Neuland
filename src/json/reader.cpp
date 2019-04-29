#include "json/reader.hpp"
#include <fstream>

std::string fileReader(std::string path)
{
    return fileReader(path.c_str());
}

std::string fileReader(const char* path)
{
    std::string content;

    std::ifstream file(path, std::ios::in);

    {
        std::string buffer;
        while (!file.eof())
        {
            std::getline(file, buffer);
            if (!buffer.empty())
                content += buffer;
        }
    }

    return content;
}