#include <cstring>
#include <fstream>

#include <iostream>
#include "backend/config.hpp"

/**
 * @brief      checks if a input stream is empty
 * @retval     bool   returns if the stream is going to be empty or not
 *
 * @param      pFile  The file
 *
 * @return     is stream eof
 */
bool isEmpty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof() || pFile.eof();
}

namespace Config
{
/**
 * @brief      reads given config file
 * @retval     Json::Value  parsaed file content
 *
 * @param      path         The path
 *
 *             Reads config file from a given path and returns it parsed
 *
 * @return     parsed config file
 */
Json::Value readConfig(std::string path)
{
    Json::Value config;

    std::ifstream file(path.c_str());

    while (file.good() && !isEmpty(file))
    {
        try
        {
            file >> config;
        }
        catch (Json::RuntimeError& param)
        {
            // catches invalid or malformed json
            std::cerr << "Config seems to be malformed" << std::endl;
        }
    }

    return config;
}
} // namespace Config