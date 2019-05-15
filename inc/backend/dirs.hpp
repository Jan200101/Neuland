#ifndef BACKEND_DIRS_HPP
#define BACKEND_DIRS_HPP

#include <string>

namespace Backend
{
int makeDirectory(std::string path);
int makeConfigdir();

const std::string getConfigdir(const std::string& home = "");
std::string getHomedir();

} // namespace Backend

#endif