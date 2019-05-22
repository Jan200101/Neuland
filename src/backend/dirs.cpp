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
 * @brief creates a directory
 * creates a directory in the given path with the permissions `rwxr-xr-x.`
 * @return int
 * @retval mkdir status code
 * @param path directory that will be created
 */
bool makeDirectory(std::string path)
{
    if (fs::is_directory(path))
        return true; // same value as create_directory would return when the directory is created
    return fs::create_directory(path);
}

/**
 * @brief creates the config directory for the current user
 * @return int
 * @retval return code of makeDirectory
 */
bool makeConfigdir()
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
    path = "\\.";
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
 */
const std::string getHomedir()
{
#ifdef __WIN32

    WCHAR path[MAX_PATH + 1];
    if (SHGetSpecialFolderPathW(HWND_DESKTOP, path, CSIDL_DESKTOPDIRECTORY, FALSE))
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

} // namespace Backend