#include <cstdlib>
#include <string>

#include "backend/dirs.hpp"
#include "defines.hpp"

namespace backend
{
std::string getConfigdir(std::string root)
{
    std::string path;
#ifdef __WIN32
    path = "/.";
#elif __unix__
    path = "/.local/share/";
#endif

    return root + path + NAME_LOWER;
}

/**
 * @brief returns the users home directory
 */
std::string getHomedir()
{
#ifdef __WIN32
    return "";

#elif __unix__
    return std::getenv("HOME");

#endif
}

} // namespace backend