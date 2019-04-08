#pragma once

#include "Event.h"

namespace dmn
{
	class MouseMovedEvent : public Event
	{
	private:
		double m_x;
		double m_y;

	public:
		inline MouseMovedEvent(double x, double y)
			: m_x(x), m_y(y)
		{
		}

		inline double getX() const { return m_x; }
		inline double getY() const { return m_y; }
	};

	class MouseButtonEvent : public Event
	{
	protected:
		int m_button;
		int m_mods;

		inline MouseButtonEvent(int button, int mods)
			: m_button(button), m_mods(mods)
		{
		}

		inline int getButton() const { return m_button; }
		inline int getMods() const { return m_mods; }
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		inline MouseButtonPressedEvent(int button, int mods)
			: MouseButtonEvent(button, mods)
		{
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		inline MouseButtonReleasedEvent(int button, int mods)
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
		inline MouseScrolledEvent(double xOffset, double yOffset)
			: m_xOffset(xOffset), m_yOffset(yOffset)
		{
		}

		inline double getXOffset() const { return m_xOffset; }
		inline double getYOffset() const { return m_yOffset; }
	};
}
