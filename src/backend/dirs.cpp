#include <cstdlib>

#include "backend/dirs.hpp"
#include "defines.hpp"

namespace backend
{
std::string getHomedir()
{
    if (const char* home = std::getenv("HOME"))
        return std::string(home);
    return "";
}

} // namespace backend