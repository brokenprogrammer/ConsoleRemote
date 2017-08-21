#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H
#pragma once

#include <string>
#include <map>
#include "WebsiteAuto.h"

class ActionHandler
{
public:
	ActionHandler();
	ActionHandler(const ActionHandler&) = default;
	~ActionHandler();

	ActionHandler& operator =(const ActionHandler&) = default;

	void handleAction();

private:
	enum Action
	{
		StartBrowser,
		OpenWebsite,
		ClickWebsite
	};

	std::map<std::string, Action> Actions;

	WebsiteAuto webAuto;
};

#endif