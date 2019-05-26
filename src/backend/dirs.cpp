#include <sys/stat.h>
#include <cstdlib>
#include <filesystem>

#ifdef __WIN32
#include <shlobj.h>
#endif

#include "backend/dirs.hpp"
#include "defines.hpp"

namespace fs = std::filesystem;

namespace Backend
{
/**
 * @brief      creates a directory creates a directory in the given path with
 *             the permissions `rwxr-xr-x.`
 *
 * @param      path   directory that will be created
 *
 * @return     int
 * @retval     mkdir  status code
 */
bool makeDirectory(std::string path)
{
    if (fs::is_directory(path))
        return true; // same value as create_directory would return when the directory is created

    try
    {
        return fs::create_directory(path);
    }
    catch (std::filesystem::__cxx11::filesystem_error& e) // catch various fs errors (like the parent not existing)
    {
        return false;
    }
}

/**
 * @brief      creates the config directory for the current user
 *
 * @return     int
 * @retval     return  code of makeDirectory
 */
bool makeConfigdir()
{
    return Backend::makeDirectory(Backend::getConfigdir());
}

/**
 * @brief      creates the card directory
 *
 * @return     int
 * @retval     return  code of makeDirectory
 */
bool makeCarddir()
{
    return Backend::makeDirectory(Backend::getCarddir());
}

/**
 * @brief      returns the users home directory
 *
 * @return     std::string
 * @retval     the   path to the users home directory
 */
const std::string getHomedir()
{
#ifdef __WIN32

    WCHAR path[MAX_PATH + 1];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path)))
    {
        std::wstring ws(path);
        std::string str(ws.begin(), ws.end());
        return str;
    }
    else
        return std::getenv("APPDATA");

#elif __unix__
    return std::getenv("HOME");

#endif
}

/**
 * @brief      return the users config directory return the config directory
 *             relative to a users home directory and appends it to the given
 *             home directory
 *
 * @param      home  path the config directory gets appended to
 *
 * @return     std::string
 * @retval     the   path relative to the users home directory
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
 * @brief return the users card directory
 * return the card directory relative to a users home directory and appends it to the given home directory
 * @return std::string
 * @retval the path relative to the users home directory
 * @param home path the config directory gets appended to
 */
const std::string getCarddir(const std::string& home)
{
    return Backend::getConfigdir(home) + "/cards/";
}

} // namespace Backend