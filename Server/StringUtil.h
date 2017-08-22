#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#pragma once

#include <string>

namespace StringUtil
{
	std::string trim(std::string target)
	{
		std::string whitespaces(" \t\f\v\n\r");
		size_t pos = target.find_last_not_of(whitespaces);

		if (pos != std::string::npos)
		{
			target.erase(pos+1);
		}
		else
		{
			target.clear();
		}

		return target;
	}
}

#endif
