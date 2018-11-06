#pragma once

#include "Core.h"

namespace dmn
{
	class DAEMON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};
}
