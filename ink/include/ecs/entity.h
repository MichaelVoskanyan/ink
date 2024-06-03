#ifndef INK_ENTITY_H
#define INK_ENTITY_H

#include <vector>
#include <memory>

/* -- Forward Declarations -- */
class Component;

class Entity {
private:
  std::vector<std::shared_ptr<Component>> components;

public:
  void Init();
  void Start();
  void Update(float deltaTime);
  void PhysicsUpdate(float fixedDeltaTime);
  void LateUpdate(float deltaTime);
};

#endif