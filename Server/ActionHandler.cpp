#include "ActionHandler.h"

ActionHandler::ActionHandler()
{
	Actions["StartBrowser"] = StartBrowser;
	Actions["OpenWebsite"]  = OpenWebsite;
	Actions["ClickWebsite"] = ClickWebsite;
}

ActionHandler::~ActionHandler()
{

}

void ActionHandler::handleAction()
{
	switch (Actions["test"])
	{
	case StartBrowser:
		webAuto.start();
		break;
	case OpenWebsite:
		webAuto.open("somestring");
	default:
		break;
	}
}