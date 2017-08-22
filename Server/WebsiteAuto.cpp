#include "WebsiteAuto.h"
#include <Python.h>
#include <iostream>

WebsiteAuto::WebsiteAuto()
{
	std::cout << "Starting browser.." << std::endl;
	
	Py_Initialize();
}

WebsiteAuto::~WebsiteAuto()
{
	Py_Finalize();

	std::cout << "Browser successfully running." << std::endl;
}

void WebsiteAuto::start()
{
	PyObject *obj = Py_BuildValue("s", "browser.py");
	FILE *file = _Py_fopen_obj(obj, "r+");

	if (file != nullptr)
	{
		PyRun_SimpleFile(file, "browser.py");
	}
}

void WebsiteAuto::open(const char* content)
{
	std::string beg = "navigateTo(\"";
	std::string end = "\")";
	std::string action = beg + content + end;

	PyRun_SimpleString(action.c_str());
}