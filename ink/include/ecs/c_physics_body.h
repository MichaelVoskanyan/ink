#pragma once

#include "component.h"

class CPhysicsBody : public Component {
public:
  CPhysicsBody(Entity* owner) : Component(owner) {}

  void Init() override;
  void Start() override;
  void Update(float deltaTime) override;
  void PhysicsUpdate(float fixedDeltaTime) override;
  void LateUpdate() override;
  CPhysicsBody(glm::vec3 position, glm::vec3 size);

  void Velocity(glm::vec3 v);
  glm::vec3 Velocity() const;

  void Acceleration(glm::vec3 a);
  glm::vec3 Acceleration() const;

  void UpdatePositionRef(float deltaTime, glm::vec3& position);

  void UpdateCollisions(bool collision);

protected:
  glm::vec3 _acceleration;
  glm::vec3 _velocity;
  bool prevCollision;
  bool currCollision;
  const float GRAVITY = 9.81f; // acceleration due to gravity
};
