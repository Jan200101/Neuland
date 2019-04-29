#ifndef JSON_WRITER_H
#define JSON_WRITER_H
#include <string>

bool fileWriter(std::string path, std::string content);
bool fileWriter(const char* path, std::string content);

#endif