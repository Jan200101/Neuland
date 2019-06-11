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
			"answers": [
				["false answer", false],
				["right answer", true]
			]
		}
	]
}
 */

namespace Config
{
Json::Value readConfig();
Json::Value readCard(const std::string& name);

bool writeConfig(Json::Value config);
bool writeCard(const std::string& name, Json::Value card);
} // namespace Config

#endif