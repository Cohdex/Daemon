#pragma once

#include "Daemon/Core.h"

#include "Daemon/Events/Event.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeinfo>
#include <type_traits>
#include <any>

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace dmn
{
	class EventDispatcher
	{
		EventDispatcher(const EventDispatcher&) = delete;
		EventDispatcher& operator=(const EventDispatcher&) = delete;

		template<typename T>
		using EventListenerFn = std::function<void(T&)>;

	private:
		static std::unique_ptr<EventDispatcher> s_instance;

		std::unordered_map<size_t, std::vector<std::any>> m_listeners;

		EventDispatcher() = default;

	public:
		DMN_API static EventDispatcher& getInstance();

		template<typename T>
		DMN_API inline void addListener(EventListenerFn<T> listener)
		{
			static_assert(std::is_base_of<Event, T>(), "Can only listen to derived types of dmn::Event");
			size_t typeHash = typeid(T).hash_code();
			m_listeners[typeHash].push_back(listener);
		}

		template<typename T>
		DMN_API inline void dispatch(T& e)
		{
			static_assert(std::is_base_of<Event, T>(), "Can only dispatch derived types of dmn::Event");
			auto eventListeners = m_listeners.find(typeid(T).hash_code());
			if (eventListeners != m_listeners.end())
			{
				for (std::any& listener : eventListeners->second)
				{
					std::any_cast<EventListenerFn<T>>(listener)(e);
				}
			}
		}
	};
}
