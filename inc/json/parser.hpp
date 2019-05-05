#ifndef JSON_PARSER_H
#define JSON_PARSER_H
#include <string>
#include "json/defines.hpp"

JSON toJson(std::string);
std::string toString(JSON);

#endif