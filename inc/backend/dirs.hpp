#ifndef BACKEND_DIRS_HPP
#define BACKEND_DIRS_HPP

#include <string>

namespace Backend
{
bool makeDirectory(std::string path);
bool makeConfigdir();
bool makeCarddir();

const std::string getHomedir();
const std::string getConfigdir(const std::string& home = Backend::getHomedir());
const std::string getCarddir(const std::string& home = Backend::getHomedir());

} // namespace Backend

#endif