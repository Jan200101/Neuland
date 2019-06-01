#ifndef BACKEND_FILES_HPP
#define BACKEND_FILES_HPP

#include <string>

namespace Backend
{
bool makeFile(const std::string& path);
bool makeConfigfile(const std::string& filename = "config.json");

} // namespace Backend

#endif // BACKEND_FILES_HPP