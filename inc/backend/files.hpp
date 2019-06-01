#ifndef BACKEND_FILES_HPP
#define BACKEND_FILES_HPP

#include <json/json.h>
#include <fstream>
#include <string>

namespace Backend
{
bool isEmpty(std::ifstream& pFile);

bool makeFile(const std::string& path);
bool makeConfigfile(const std::string& filename = "config.json");

Json::Value parseFile(std::ifstream& file);
} // namespace Backend

#endif // BACKEND_FILES_HPP