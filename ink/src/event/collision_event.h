#ifndef INK_COLLISION_EVENT
#define INK_COLLISION_EVENT

#include "event.h"

#include <ecs/entity.h>
#include <ecs/components/c_box_collider.h>
#include <typedefs.h>

class CollisionEvent : public Event
{
    Entity *entityA;
    Entity *entityB;

    EventType get_event_type() {
        return EventType::app_update;
    }

    CollisionEvent(Entity *a, Entity *b) : entityA(a), entityB(b) {}
    ~CollisionEvent()
    {
        entityA = entityB = nullptr;
    }
};

#endif // INK_COLLISION_EVENT