#pragma once

#include "Daemon/Core.h"

#include "Event.h"

namespace dmn
{
	class MouseMovedEvent : public Event
	{
	private:
		double m_x;
		double m_y;

	public:
		DMN_API inline MouseMovedEvent(double x, double y)
			: m_x(x), m_y(y)
		{
		}

		DMN_API inline double getX() const { return m_x; }
		DMN_API inline double getY() const { return m_y; }
	};

	class MouseButtonEvent : public Event
	{
	protected:
		int m_button;
		int m_mods;

		DMN_API inline MouseButtonEvent(int button, int mods)
			: m_button(button), m_mods(mods)
		{
		}

		DMN_API inline int getButton() const { return m_button; }
		DMN_API inline int getMods() const { return m_mods; }
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		DMN_API inline MouseButtonPressedEvent(int button, int mods)
			: MouseButtonEvent(button, mods)
		{
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		DMN_API inline MouseButtonReleasedEvent(int button, int mods)
			: MouseButtonEvent(button, mods)
		{
		}
	};

	class MouseScrolledEvent : public Event
	{
	private:
		double m_xOffset;
		double m_yOffset;

	public:
		DMN_API inline MouseScrolledEvent(double xOffset, double yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset)
		{
		}

		DMN_API inline double getXOffset() const { return m_xOffset; }
		DMN_API inline double getYOffset() const { return m_yOffset; }
	};
}
