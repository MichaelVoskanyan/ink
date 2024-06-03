#ifndef INK_COMPONENT_H
#define INK_COMPONENT_H

#include <memory>
#include <glm/glm.hpp>

/* -- Forward Declaration -- */
class Entity;

class Component {
protected:
  std::shared_ptr<Entity> owner;

public:
  Component(Entity* owner) : owner(owner) {}
  ~Component() {}

  virtual void init() {}
  virtual void start() {}
  virtual void update(float deltaTime) {}
  virtual void physicsUpdate(float fixedDeltaTime) {}
  virtual void lateUpdate(float deltaTime) {}
};

#endif