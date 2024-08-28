#ifndef INK_COLLISION_EVENT
#define INK_COLLISION_EVENT

#include "event.h"

#include <ecs/entity.h>
#include <ecs/components/c_box_collider.h>
#include <typedefs.h>

class collisionEvent_t : public event_t
{
public:
    entity_t *entityA;
    entity_t *entityB;
    glm::vec2 overlap;

    eventType_t GetEventType() const override
    {
        return GetStaticType();
    }

    static eventType_t GetStaticType()
    {
        return eventType_t::CollisionUpdate;
    }

    collisionEvent_t(entity_t *a, entity_t *b, glm::vec2 overlap) : entityA(a), entityB(b), overlap(overlap) {}
    ~collisionEvent_t()
    {
        entityA = entityB = nullptr;
    }
};

#endif // INK_COLLISION_EVENT
