#ifndef INK_COMPONENT_H
#define INK_COMPONENT_H

#include <memory>
#include <glm/glm.hpp>

/* -- Forward Declaration -- */
class entity_t;

class component_t
{
protected:
    entity_t *owner_;

public:
    component_t(entity_t *owner) :owner_(owner) {}

    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void LateUpdate() = 0;

    inline entity_t* GetOwner() const { return owner_; }
};

#endif
