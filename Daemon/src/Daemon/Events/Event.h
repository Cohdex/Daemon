#pragma once

namespace dmn
{
	class Event
	{
	protected:
		bool m_handled = false;

	public:
		virtual ~Event() {}

		inline bool isHandled() const { return m_handled; }
		inline void setHandled(bool handled) { m_handled = handled; }
	};
}
