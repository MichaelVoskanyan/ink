#ifndef INK_EVENT_H
#define INK_EVENT_H

enum class EventType
{
    none = 0,
    window_resize,
    window_close,
    app_tick,
    app_update
};

class Event
{
public:
    virtual ~Event() = default;
    virtual EventType get_event_type() const = 0;

    bool m_handled = false;
};

class EventDispatcher
{
public:
    EventDispatcher(Event& event)
        : _event(event) {}

    template <typename T, typename F>
    bool Dispatch(const F& func)
    {
        if (_event.get_event_type == T::get_static_type())
        {
            _event.m_handled |= func(static_cast<T&>(_event));
            return true;
        }
        return false;
    }

private:
    Event& _event;
};

#endif // INK_EVENT_H