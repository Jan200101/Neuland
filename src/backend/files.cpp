#include <ctime>
#include <fstream>

#include "backend/dirs.hpp"
#include "backend/files.hpp"

namespace Backend
{
/**
 * @brief      checks if a input stream is empty
 * @retval     bool   returns if the stream is going to be empty or not
 *
 * @param      pFile  the input stream
 *
 * @return     is stream eof
 */
bool isEmpty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof() || pFile.eof();
}

/**
 * @brief      opens a output file stream and returns the good status
 *
 * @param[in]  path  path to the file that will be created
 *
 * @return     bool
 */
bool makeFile(const std::string& path)
{
    std::ofstream file;

    file.open(path, std::ios::app); // append so the contents don't get overwritten

    return file.good();
}

/**
 * @brief      calls Backend::makeFile onto a file in the config directory
 *
 * @param[in]  filename  name of the file thats going to be created
 *
 * @return     bool
 */
bool makeConfigfile(const std::string& filename)
{
    return Backend::makeFile(Backend::getConfigdir() + "/" + filename);
}

Json::Value parseFile(std::ifstream& file)
{
    Json::Value conf;

    if (file.good() && !Backend::isEmpty(file))
    {
        try
        {
            file >> conf;
        }
        catch (Json::RuntimeError& param)
        {
            // pass
        }
    }

    return conf;
}

} // namespace Backend