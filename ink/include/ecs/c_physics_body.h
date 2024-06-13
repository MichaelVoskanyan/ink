#pragma once

#include "component.h"

class CPhysicsBody : public Component {
public:
  CPhysicsBody(Entity* owner) : Component(owner) {}

  void Init();
  void Start();
  void Update(float deltaTime);
  void PhysicsUpdate(float fixedDeltaTime);
  void LateUpdate(float deltaTime);
  //PhysicsBody(glm::vec3 position, glm::vec3 size);

  void Velocity(glm::vec3 v);
  glm::vec3 Velocity() const;

  void Acceleration(glm::vec3 a);
  glm::vec3 Acceleration() const;

  void UpdatePositionRef(float deltaTime, glm::vec3 &position);
  
private:
  glm::vec3 _acceleration;
  glm::vec3 _velocity;
  // glm::vec3 _size;               // bounding box for collision detection
  const float GRAVITY = 0.1f;    // acceleration due to gravity
};
