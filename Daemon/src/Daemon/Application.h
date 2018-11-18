#pragma once

#include "Core.h"

namespace dmn
{
	class DMN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};
}
