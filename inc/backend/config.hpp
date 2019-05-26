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
Json::Value readCard(std::string path);
Json::Value readConfig(std::string path);

bool writeConfig(Json::Value config, std::string path);
} // namespace Config

#endif