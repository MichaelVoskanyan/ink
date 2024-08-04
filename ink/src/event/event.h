#ifndef INK_EVENT_H
#define INK_EVENT_H

#include <typedefs.h>
#include <functional>
#include <utility>

enum class EventType
{
	NONE = 0, APP_EVENT, WINDOW_EVENT, INPUT_EVENT
};

struct Event
{
	EventType eventType;
	std::function<void()> eventHandler;

	Event(EventType type, std::function<void()> handler)
		: eventType(type), eventHandler(std::move(handler))
	{
	}
};

struct WindowEvent : public Event
{
	WindowEvent(EventType type, std::function<void()> handler) : Event(EventType::WINDOW_EVENT, std::move(handler))
	{}
};

struct WindowResizeEvent : public WindowEvent
{
	WindowResizeEvent(std::function<void()> handler) : WindowEvent(EventType::WINDOW_EVENT, std::move(handler)){}
};

struct WindowCloseEvent : public WindowEvent
{
	WindowCloseEvent(std::function<void()> handler) : WindowEvent(EventType::WINDOW_EVENT, std::move(handler)) {}
};

class EventBus
{
	Vec<Event> m_eventQueue;
	EventBus()
	{
		m_eventQueue = Vec<Event>();
	}

	static EventBus* s_instance;

public:
	EventBus(const EventBus& e) = delete;
	EventBus& operator=(const EventBus& e) = delete;

public:
	static EventBus* get_instance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new EventBus();
		}
		return s_instance;
	}

	void add_to_queue(Event e)
	{
		m_eventQueue.emplace_back(e);
	}
	void handle_queue()
	{
		auto it = m_eventQueue.begin();

		for (it; it != m_eventQueue.end(); it++)
		{
			it->eventHandler();
		}

		m_eventQueue.clear();
	}
};

#endif