#pragma once

#include "Daemon/Core.h"

namespace dmn
{
	class Event
	{
	protected:
		bool m_handled = false;

	public:
		DMN_API virtual ~Event() {}

		DMN_API inline bool isHandled() const { return m_handled; }
		DMN_API inline void setHandled(bool handled) { m_handled = handled; }
	};
}
