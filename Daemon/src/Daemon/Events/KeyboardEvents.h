#pragma once

#include "Daemon/Core.h"

#include "Event.h"

namespace dmn
{
	class KeyEvent : public Event
	{
		friend class KeyPressedEvent;
		friend class KeyReleasedEvent;

	private:
		int m_key;
		int m_mods;

		DMN_API inline KeyEvent(int key, int mods)
			: m_key(key), m_mods(mods)
		{
		}

	public:
		DMN_API inline int getKey() const { return m_key; }
		DMN_API inline int getMods() const { return m_mods; }
	};

	class KeyPressedEvent : public KeyEvent
	{
	private:
		bool m_repeated;

	public:
		DMN_API inline KeyPressedEvent(int key, int mods, bool repeated)
			: KeyEvent(key, mods), m_repeated(repeated)
		{
		}

		DMN_API inline bool isRepeated() const { return m_repeated; }
	};

	class KeyReleasedEvent : public KeyEvent
	{
	private:

	public:
		DMN_API inline KeyReleasedEvent(int key, int mods)
			: KeyEvent(key, mods)
		{
		}
	};
}
