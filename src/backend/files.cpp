#include <ctime>
#include <fstream>

#include "backend/dirs.hpp"
#include "backend/files.hpp"

namespace Backend
{
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
} // namespace Backend