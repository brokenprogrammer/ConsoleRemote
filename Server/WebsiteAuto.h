#pragma once

#include <string>

class WebsiteAuto
{
public:
	WebsiteAuto();
	WebsiteAuto(const WebsiteAuto&) = default;
	~WebsiteAuto();

	WebsiteAuto& operator =(const WebsiteAuto&) = default;

	void open(const char* content);

private:
	std::string currentUrl;
};