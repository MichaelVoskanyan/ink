#ifndef INK_MOVEMENT_EVENT
#define INK_MOVEMENT_EVENT

#include "event.h"

#include <ecs/entity.h>
#include <typedefs.h>
#include <memory>

class movementEvent_t : public event_t
{
public:
    int keyPress_;
    float deltaTime_;
    std::shared_ptr<entity_t> player_;

    eventType_t GetEventType() const override
    {
        return GetStaticType();
    }

    static eventType_t GetStaticType()
    {
        return eventType_t::MovementUpdate;
    }

    movementEvent_t(int keyPress, float deltaTime, std::shared_ptr<entity_t> player)
        : keyPress_(keyPress), deltaTime_(deltaTime), player_(player) {};
    ~movementEvent_t() {}
};

#endif // INK_MOVEMENT_EVENT
