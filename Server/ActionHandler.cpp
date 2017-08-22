#include "ActionHandler.h"
#include "StringUtil.h"
#include <iostream>

ActionHandler::ActionHandler()
{
	Actions["StartBrowser"] = StartBrowser;
	Actions["OpenWebsite"]  = OpenWebsite;
	Actions["ClickWebsite"] = ClickWebsite;
	Actions["ExitBrowser"]  = ExitBrowser;
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
		command = StringUtil::trim(commandList.front());
		webAuto.open(command.c_str());
		commandList.erase(commandList.begin());
		break;
	case ClickWebsite:
		break;
	case ExitBrowser:
		break;
	default:
		break;
	}
}