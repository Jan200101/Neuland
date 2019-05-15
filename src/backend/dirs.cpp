#include <sys/stat.h>
#include <cstdlib>

#include "backend/dirs.hpp"
#include "defines.hpp"

namespace Backend
{
/**
 * @brief creates a directory
 * creates a directory in the given path with the permissions `rwxr-xr-x.`
 * @return int
 * @retval mkdir status code
 * @param path directory that will be created
 * \todo add check to see if the directory exists
 */
// TODO add check to see if the directory exists
int makeDirectory(const char* path)
{
    return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

/**
 * @brief creates a directory
 * creates a directory in the given path with the permissions `rwxr-xr-x.`
 * @return int
 * @retval mkdir status code
 * @param path directory that will be created
 */
// TODO add check to see if the directory exists
int makeDirectory(std::string path)
{
    return Backend::makeDirectory(path.c_str());
}

/**
 * @brief creates the config directory for the current user
 * @return int
 * @retval mkdir status code
 */
int makeConfigdir()
{
    return Backend::makeDirectory(Backend::getConfigdir(Backend::getHomedir()));
}

/**
 * @brief return the users config directory
 * return the config directory relative to a users home directory and appends it to the given home directory
 * @return std::string
 * @retval the path relative to the users home directory
 * @param home path the config directory gets appended to
 */
const std::string getConfigdir(const std::string& home)
{
    std::string path;
#ifdef __WIN32
    path = "/.";
#elif __unix__
    path = "/.local/share/";
#endif

    path = home + path + NAME_LOWER;

    return path;
}

/**
 * @brief returns the users home directory
 * @return std::string
 * @retval the path to the users home directory
 * \todo implement home fetching on windows
 */
// TODO implement home fetching on windows
std::string getHomedir()
{
#ifdef __WIN32
    return "";

#elif __unix__
    return std::getenv("HOME");

#endif
}

} // namespace Backend