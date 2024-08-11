#ifndef INK_COMPONENT_H
#define INK_COMPONENT_H

#include <memory>
#include <glm/glm.hpp>

/* -- Forward Declaration -- */
class Entity;

class Component
{
protected:
    Entity *m_owner;

public:
    Component(Entity *owner) :m_owner(owner) {}

    virtual void init() = 0;
    virtual void start() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void late_update() = 0;

    inline Entity* get_owner() const { return m_owner; }
};

#endif