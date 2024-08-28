#ifndef INK_EVENT_H
#define INK_EVENT_H

enum class eventType_t
{
    None = 0,
    WindowResize,
    WindowClose,
    AppTick,
    AppUpdate,
    CollisionUpdate,
    PhysicsUpdate,
    MovementUpdate
};

class event_t
{
public:
    virtual ~event_t() = default;
    virtual eventType_t GetEventType() const = 0;

    bool handled_ = false;
};

class eventDispatcher_t
{
public:
    eventDispatcher_t(event_t &event) : event_(event) {}

    template <typename T, typename F>
    bool Dispatch(const F &func)
    {
        if(event_.GetEventType() == T::GetStaticType())
        {
            event_.handled_ |= func(static_cast<T &>(event_));
            return true;
        }
        return false;
    }

private:
    event_t &event_;
};

#endif // INK_EVENT_H
