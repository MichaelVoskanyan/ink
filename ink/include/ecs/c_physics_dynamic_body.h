#pragma once

#include "c_physics_body.h"

class CPhysicsDynamicBody : public CPhysicsBody {
public:
  CPhysicsDynamicBody(Entity* owner) : CPhysicsBody(owner) {}

  void Init();
  void Start();
  void Update(float deltaTime);
  void PhysicsUpdate(float fixedDeltaTime);
  void LateUpdate();

  void Velocity(glm::vec3 v);
  glm::vec3 Velocity() const;

  void Acceleration(glm::vec3 a);
  glm::vec3 Acceleration() const;
  void UpdatePositionRef(float deltaTime, glm::vec3& position);
  void UpdateCollisions(bool collision);

  private:
    const float GRAVITY = 5.5f; // acceleration due to gravity
    glm::vec3 _acceleration;
    glm::vec3 _velocity;
    bool prevCollision;
    bool currCollision;
};