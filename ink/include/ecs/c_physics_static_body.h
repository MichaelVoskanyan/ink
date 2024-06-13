#pragma once

#include "c_physics_body.h"

class CPhysicsStaticBody : public CPhysicsBody {
public:
  CPhysicsStaticBody(Entity* owner) : CPhysicsBody(owner) {}

  void Init() {}
  void Start() {}
  void Update(float deltaTime) {}
  void PhysicsUpdate(float fixedDeltaTime) {}
  void LateUpdate() {}
  void UpdatePositionRef(float deltaTime, glm::vec3& position) {}
  // void UpdateCollisions(bool collision) {}

};