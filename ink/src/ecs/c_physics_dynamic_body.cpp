#include <ecs/c_physics_dynamic_body.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>
#include <iostream>

void CPhysicsDynamicBody::Init() {
  _acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f);
  _velocity = glm::vec3(0.0f);
  prevCollision = false;
  currCollision = false;
}

void CPhysicsDynamicBody::Start() {}

void CPhysicsDynamicBody::Update(float deltaTime) {}

void CPhysicsDynamicBody::PhysicsUpdate(float fixedDeltaTime) {
  UpdatePositionRef(fixedDeltaTime, owner->position);
}

void CPhysicsDynamicBody::LateUpdate() {}

void CPhysicsDynamicBody::UpdateCollisions(bool collision) {
  prevCollision = currCollision;
  currCollision = collision;
}

void CPhysicsDynamicBody::Velocity(glm::vec3 v) {
  _velocity = v;
}

glm::vec3 CPhysicsDynamicBody::Velocity() const {
  return _velocity;
}

void CPhysicsDynamicBody::Acceleration(glm::vec3 a) {
  _acceleration = a;
}

glm::vec3 CPhysicsDynamicBody::Acceleration() const {
  return _acceleration;
}

void CPhysicsDynamicBody::UpdatePositionRef(float deltaTime, glm::vec3& position) {
  if(prevCollision && currCollision) {
    _velocity.x = 0; _velocity.y = 0;
  }
  else if (currCollision)
  {
    _velocity.y = -0.9f * _velocity.y;
  }
  else {
    _velocity += _acceleration * deltaTime;
  }
  position += _velocity * deltaTime;
  std::cout << "Current Velocity: " << _velocity.y << std::endl;
  std::cout << "Current Acceleration: " << _acceleration.y << std::endl;
}