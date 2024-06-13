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

  virtual void Init() = 0;
  virtual void Start() = 0;
  virtual void Update(float deltaTime) = 0;
  virtual void LateUpdate() = 0;
};

#endif