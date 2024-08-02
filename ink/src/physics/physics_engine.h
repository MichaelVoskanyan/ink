#ifndef INK_PHYSICSENGINE_H
#define INK_PHYSICSENGINE_H

#include <vector>
#include <memory>
#include "physics_base.h"

class PhysicsEngine {
public:
  PhysicsEngine();

  void add_physics_body(std::shared_ptr<PhysicsBody> body);
  void remove_physics_body(std::shared_ptr<PhysicsBody> body);

  void update(float deltaTime);
  void handle_collisions();

private:
  std::vector<std::shared_ptr<PhysicsBody>> m_bodies;
  bool check_collision(const PhysicsBody& body1, const PhysicsBody& body2);
  void resolve_collision(PhysicsBody& body1, PhysicsBody& body2);
};

#endif // INK_PHYSICSENGINE_H