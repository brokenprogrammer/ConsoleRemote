#ifndef ACTIONPARSER_H
#define ACTIONPARSER_H
#pragma once

#include <string>
#include <vector>

class ActionParser
{
public:
	ActionParser();
	~ActionParser();

	std::vector<std::string> parseMessage(std::string message);

private:
	static const std::string delimiter;
};

#endif
