#pragma once

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
		inline WindowResizedEvent(int width, int height)
			: m_width(width), m_height(height)
		{
		}

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	};
}
