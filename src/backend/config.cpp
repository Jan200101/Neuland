#include <cstring>
#include <fstream>

#include <iostream>
#include "backend/config.hpp"

namespace Config
{
/**
 * @brief checks if a input stream is empty
 * @return bool
 * @retval is stream eof
 */
bool isEmpty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

/**
 * @brief reads given config file
 * @return Json::Value
 * @retval parsed config file
 * @param path
 *
 * Reads config file from a given path and returns it parsed
 */
Json::Value readConfig(std::string path)
{
    Json::Value config;

    std::ifstream file(path.c_str());

    while (file.good() && !Config::isEmpty(file))
    {
        file >> config;
    }

    return config;
}
} // namespace Config