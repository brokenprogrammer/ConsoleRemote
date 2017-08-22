#include "ActionHandler.h"
#include "StringUtil.h"
#include <iostream>

ActionHandler::ActionHandler()
{
	Actions[std::string("StartBrowser")] = StartBrowser;
	Actions["OpenWebsite"]  = OpenWebsite;
	Actions["ClickWebsite"] = ClickWebsite;
}

ActionHandler::~ActionHandler()
{

}

void ActionHandler::handleAction(std::vector<std::string> commandList)
{
	std::string command = commandList.front();
	commandList.erase(commandList.begin());

	switch (Actions[StringUtil::trim(command)])
	{
	case StartBrowser:
		std::cout << "Starting browser.." << std::endl;
		webAuto.start();
		break;
	case OpenWebsite:
		webAuto.open("somestring");
	default:
		break;
	}
}