#ifndef INK_PHYSICSENGINE_H
#define INK_PHYSICSENGINE_H

#include <vector>
#include <memory>
#include "physics_base.h"

class PhysicsEngine {
public:
  PhysicsEngine();

  void AddPhysicsBody(std::shared_ptr<PhysicsBody> body);
  void RemovePhysicsBody(std::shared_ptr<PhysicsBody> body);

  void Update(float deltaTime);
  void HandleCollisions();

private:
  std::vector<std::shared_ptr<PhysicsBody>> _bodies;
  bool CheckCollision(const PhysicsBody& body1, const PhysicsBody& body2);
  void ResolveCollision(PhysicsBody& body1, PhysicsBody& body2);
};

#endif // INK_PHYSICSENGINE_H