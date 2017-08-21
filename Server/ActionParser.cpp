#include "ActionParser.h"
#include <iostream>

const std::string ActionParser::delimiter = " ";

ActionParser::ActionParser()
{

}

ActionParser::~ActionParser()
{

}

std::vector<std::string> ActionParser::parseMessage(std::string message)
{
	std::vector<std::string> commandList;

	size_t pos = 0;
	std::string token;
	while ((pos = message.find(delimiter)) != std::string::npos) 
	{
		token = message.substr(0, pos);
		// Store token
		commandList.push_back(token);

		message.erase(0, pos + 1);
	}
	// Add last argument manually.
	commandList.push_back(message);
	
	return commandList;
}