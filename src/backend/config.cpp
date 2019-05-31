#include <cstring>
#include <fstream>
#include <iostream>

#include "backend/config.hpp"
#include "backend/dirs.hpp"

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
 *             Reads config file and returns it parsed
 *             if any error occures it prints to cerr and returns an empty Json
 *
 * @return     parsed config file
 * 
 * @todo       use jsoncpp reader
 */
Json::Value readConfig()
{
    Json::Value config;

    std::ifstream file((Backend::getConfigdir() + "/config.json").c_str());

    if (file.good() && !isEmpty(file))
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

/**
 * @brief      writes to the config file
 * @retval     bool  true if config was written to file 
 *
 * @retval     config        config taht needs saving
 *
 *             writes the given json object to the config file and returns if it did so successfully
 *
 * @return     return status
 * 
 * @todo       use jsoncpp writer
 */
bool writeConfig(Json::Value config)
{
    std::ofstream file((Backend::getConfigdir() + "/config.json").c_str());

    if (file.good())
    {
        file << config;
        return true;
    }

    return false;
}

} // namespace Config