#include <cstring>
#include <fstream>

#include <iostream>
#include "backend/config.hpp"

/**
 * @brief checks if a input stream is empty
 * @retval bool
 * @return is stream eof
 */
bool isEmpty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof() || pFile.eof();
}

namespace Config
{
/**
 * @brief reads given config file
 * @retval Json::Value
 * @return parsed config file
 * @param path
 *
 * Reads config file from a given path and returns it parsed
 */
Json::Value readConfig(std::string path)
{
    Json::Value config;

    std::ifstream file(path.c_str());

    while (file.good() && !isEmpty(file))
    {
        file >> config;
    }

    return config;
}
} // namespace Config