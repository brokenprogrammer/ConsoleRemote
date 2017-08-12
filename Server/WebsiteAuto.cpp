#include "WebsiteAuto.h"
#include <Python.h>
#include <iostream>

WebsiteAuto::WebsiteAuto()
{
	std::cout << "Starting browser.." << std::endl;
	
	Py_Initialize();
	PyObject *obj = Py_BuildValue("s", "browser.py");
	FILE *file = _Py_fopen_obj(obj, "r+");

	if (file != nullptr)
	{
		PyRun_SimpleFile(file, "browser.py");
	}
	
	Py_Finalize();

	std::cout << "Browser successfully running." << std::endl;
}

WebsiteAuto::~WebsiteAuto()
{

}

void WebsiteAuto::open(const char* content)
{

}