#include "pch.h"
#include "EventDispatcher.h"

namespace dmn
{
	std::unique_ptr<EventDispatcher> EventDispatcher::s_instance;

	EventDispatcher& EventDispatcher::getInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = std::unique_ptr<EventDispatcher>(new EventDispatcher());
		}
		return *s_instance;
	}
}
