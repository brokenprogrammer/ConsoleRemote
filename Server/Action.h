#ifndef ACTION_H
#define ACTION_H
#pragma once

class Action
{
public:
	Action();
	Action(const Action&) = default;
	~Action();

	Action& operator =(const Action&) = default;
};

#endif
