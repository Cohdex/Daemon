#pragma once

#include "Daemon/Core.h"

#include "Event.h"

namespace dmn
{
	class WindowCloseEvent : public Event
	{
	};

	class WindowResizedEvent : public Event
	{
	private:
		int m_width;
		int m_height;

	public:
		DMN_API inline WindowResizedEvent(int width, int height)
			: m_width(width), m_height(height)
		{
		}

		DMN_API inline int getWidth() const { return m_width; }
		DMN_API inline int getHeight() const { return m_height; }
	};
}
