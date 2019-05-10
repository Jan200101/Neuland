#ifndef BACKEND_DIRS_HPP
#define BACKEND_DIRS_HPP

#include <string>

namespace Backend
{
std::string getConfigdir(std::string = "");
std::string getHomedir();

} // namespace Backend

#endif