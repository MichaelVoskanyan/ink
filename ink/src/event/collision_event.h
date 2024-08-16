#ifndef INK_COLLISION_EVENT
#define INK_COLLISION_EVENT

#include "event.h"

#include <ecs/entity.h>
#include <ecs/components/c_box_collider.h>
#include <typedefs.h>

class CollisionEvent : public Event
{
public:
    Entity *entityA;
    Entity *entityB;
    glm::vec2 overlap;

    EventType get_event_type() const override
    {
        return get_static_type();
    }

    static EventType get_static_type()
    {
        return EventType::collision_update;
    }

    CollisionEvent(Entity *a, Entity *b, glm::vec2 overlap) : entityA(a), entityB(b), overlap(overlap) {}
    ~CollisionEvent()
    {
        entityA = entityB = nullptr;
    }
};

#endif // INK_COLLISION_EVENT