#ifndef INK_COMPONENT_H
#define INK_COMPONENT_H

#include <memory>

/* -- Forward Declaration -- */
class Entity;

class Component {
private:
  std::shared_ptr<Entity> owner;

public:
  virtual void Init();
  virtual void Start();
  virtual void Update(float deltaTime);
  virtual void PhysicsUpdate(float fixedDeltaTime);
  virtual void LateUpdate(float deltaTime);
};

#endif