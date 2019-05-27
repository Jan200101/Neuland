#ifndef BACKEND_DIRS_HPP
#define BACKEND_DIRS_HPP

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace Backend
{
bool makeFile(const std::string& path);
bool makeConfigfile(const std::string& filename = "config.json");

bool makeDirectory(const std::string& path);
bool makeConfigdir();
bool makeCarddir();

const std::string getHomedir();
const std::string getConfigdir(const std::string& home = Backend::getHomedir());
const std::string getCarddir(const std::string& home = Backend::getHomedir());

const fs::directory_iterator listDirectory(const std::string& path);
const fs::directory_iterator listConfigdir();
const fs::directory_iterator listCarddir();

} // namespace Backend

#endif