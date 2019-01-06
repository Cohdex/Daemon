#include <Daemon.h>
#include <Daemon/EntryPoint.h>

class TestApp : public dmn::Application
{
public:
	TestApp()
	{
		
	}

	~TestApp()
	{

	}
};

dmn::Application* dmn::createApplication()
{
	return new TestApp();
}
