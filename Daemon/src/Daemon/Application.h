#pragma once

#include "Core.h"

#include "Window/Window.h"
#include "Daemon/Events/WindowEvents.h"

namespace dmn
{
	class Application
	{
	private:
		bool m_running;
		std::unique_ptr<Window> m_window;

		void handleWindowCloseEvent(WindowCloseEvent& e);

	public:
		DMN_API Application();
		DMN_API virtual ~Application();

		DMN_API void run();
	};
}
