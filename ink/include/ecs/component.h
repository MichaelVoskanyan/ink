#ifndef INK_COMPONENT_H
#define INK_COMPONENT_H

#include <memory>
#include <glm/glm.hpp>

/* -- Forward Declaration -- */
class Entity;

class Component {
protected:
  Entity* owner;

public:
  Component(Entity* owner) : owner(owner) {}

  virtual void Init() {}
  virtual void Start() {}
  virtual void Update(float deltaTime) {}
  virtual void PhysicsUpdate(float fixedDeltaTime) {}
  virtual void LateUpdate(float deltaTime) {}
};

#endif