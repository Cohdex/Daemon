#pragma once

#include "Application.h"

namespace dmn
{
	// Defined by client
	extern Application* createApplication();
}

int main(int argc, char** argv)
{
	dmn::Application* application = dmn::createApplication();
	application->run();
	delete application;
	return 0;
}
