#ifndef INK_MOVEMENT_EVENT
#define INK_MOVEMENT_EVENT

#include "event.h"

#include <ecs/entity.h>
#include <typedefs.h>
#include <memory>

class MovementEvent : public Event
{
public:
    int keyPress;
    float deltaTime;
    std::shared_ptr<Entity> player;

    EventType get_event_type() const override
    {
        return get_static_type();
    }

    static EventType get_static_type()
    {
        return EventType::movement_update;
    }

    MovementEvent(int keyPress, float deltaTime, std::shared_ptr<Entity> player)
        : keyPress(keyPress), deltaTime(deltaTime), player(player) {};
    ~MovementEvent() {}
};

#endif // INK_MOVEMENT_EVENT