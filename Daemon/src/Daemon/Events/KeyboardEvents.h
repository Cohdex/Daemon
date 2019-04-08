#pragma once

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

		inline KeyEvent(int key, int mods)
			: m_key(key), m_mods(mods)
		{
		}

	public:
		inline int getKey() const { return m_key; }
		inline int getMods() const { return m_mods; }
	};

	class KeyPressedEvent : public KeyEvent
	{
	private:
		bool m_repeated;

	public:
		inline KeyPressedEvent(int key, int mods, bool repeated)
			: KeyEvent(key, mods), m_repeated(repeated)
		{
		}

		inline bool isRepeated() const { return m_repeated; }
	};

	class KeyReleasedEvent : public KeyEvent
	{
	private:

	public:
		inline KeyReleasedEvent(int key, int mods)
			: KeyEvent(key, mods)
		{
		}
	};
}
