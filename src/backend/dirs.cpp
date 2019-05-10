#include <cstdlib>
#include <string>

#include "backend/dirs.hpp"
#include "defines.hpp"

namespace backend
{
/**
 * @brief returns the users home directory
 */
std::string getHomedir()
{
#ifdef __WIN32
/**
	 * \todo implement Windows part
	 */
#elif __unix__
    const char* env = std::getenv("HOME");

    std::string home = env;

    return home;

#endif
}

} // namespace backend