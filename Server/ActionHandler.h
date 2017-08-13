#ifndef ACTIONHANDLER_H
#define ACTIONHANDLER_H
#pragma once

class ActionHandler
{
public:
	ActionHandler();
	ActionHandler(const ActionHandler&) = default;
	~ActionHandler();

	ActionHandler& operator =(const ActionHandler&) = default;

	void handleAction();
};

#endif