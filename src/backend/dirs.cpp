//#include <json/json.h>
#include <sys/stat.h>
//#include <cstdlib>
#include <ctime>
#include <fstream>

#ifdef __WIN32
#include <shlobj.h>
#endif

#include "backend/dirs.hpp"
#include "defines.hpp"

namespace Backend
{
/**
 * @brief      opens a output file stream and returns the good status
 *
 * @param      path   path to the file that will be created
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
 * @param      filename   name of the file thats going to be created
 *
 * @return     bool
 */
bool makeConfigfile(const std::string& filename)
{
    return Backend::makeFile(Backend::getConfigdir() + "/" + filename);
}

/**
 * @brief      creates a directory creates a directory in the given path with
 *
 * @param      path   directory that will be created
 *
 * @return     int
 */
bool makeDirectory(const std::string& path)
{
    if (fs::is_directory(path))
        return true; // same value as create_directory would return when the directory is created

    try
    {
        return fs::create_directory(path);
    }
    catch (fs::__cxx11::filesystem_error& e) // catch various fs errors (like the parent not existing)
    {
        return false;
    }
}

/**
 * @brief      creates the config directory for the current user
 *
 * @return     int
 */
bool makeConfigdir()
{
    return Backend::makeDirectory(Backend::getConfigdir());
}

/**
 * @brief      creates the card directory
 *
 * @return     int
 */
bool makeCarddir()
{
    return Backend::makeDirectory(Backend::getCarddir());
}

/**
 * @brief      returns the users home directory
 *
 * @return     std::string
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
 * @brief      return the users card directory
 *             return the card directory relative to a users home directory
 *             and appends it to the given home directory
 *
 * @param      home path the config directory gets appended to
 *
 * @return     std::string
 */
const std::string getCarddir(const std::string& home)
{
    return Backend::getConfigdir(home) + "/cards/";
}

const fs::directory_iterator listDirectory(const std::string& path)
{
    return fs::directory_iterator(path);
}

const fs::directory_iterator listConfigdir()
{
    return Backend::listDirectory(Backend::getConfigdir());
}

const fs::directory_iterator listCarddir()
{
    return Backend::listDirectory(Backend::getCarddir());
}

} // namespace Backend