#ifndef BACKEND_DIRS_HPP
#define BACKEND_DIRS_HPP

#include <string>

namespace Backend
{
bool makeDirectory(std::string path);
bool makeConfigdir();

const std::string getConfigdir(const std::string& home = "");
const std::string getHomedir();

} // namespace Backend

#endif