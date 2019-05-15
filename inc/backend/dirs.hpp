#ifndef BACKEND_DIRS_HPP
#define BACKEND_DIRS_HPP

#include <string>

namespace Backend
{
std::string getConfigdir(std::string = "");
const std::string getConfigdir(const std::string& root = "");
std::string getHomedir();

} // namespace Backend

#endif