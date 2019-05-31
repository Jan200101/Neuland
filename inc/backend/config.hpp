#ifndef BACKEND_CONFIG_HPP
#define BACKEND_CONFIG_HPP value

#include <json/json.h>

/*
{
    "lastedited":"UNIXTIME",
}

{
	"categories": ["categorie", "categorie"],
	"cards": [
		{
			"question": "<question>",
			"answers": {
				"right": ["right answer"],
				"false": ["false answer"]
			}
		}
	]
}
 */

namespace Config
{
Json::Value readConfig();
Json::Value readCard(std::string name);

bool writeConfig(Json::Value config);
bool writeCard(std::string name, Json::Value card);

bool createDefaultConfig(std::string path);
} // namespace Config

#endif