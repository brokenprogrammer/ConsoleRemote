#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include "WebsiteAuto.h"

class ActionHandler
{
public:
	ActionHandler();
	ActionHandler(const ActionHandler&) = default;
	~ActionHandler();

	ActionHandler& operator =(const ActionHandler&) = default;

	void handleAction(std::vector<std::string> commandList);

private:
	enum Action
	{
		StartBrowser = 1,
		OpenWebsite  = 2,
		ClickWebsite = 3
	};

	std::map<std::string, Action> Actions;

	WebsiteAuto webAuto;
};

#endif