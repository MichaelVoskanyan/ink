#include <ecs/c_physics_body.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>
#include <iostream>

void CPhysicsBody::Init() {
  // _acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f);
  // _velocity = glm::vec3(0.0f);
  // prevCollision = false;
  // currCollision = false;
}

void CPhysicsBody::Start() {}

void CPhysicsBody::Update(float deltaTime) {}

void CPhysicsBody::PhysicsUpdate(float fixedDeltaTime) {
  // UpdatePositionRef(fixedDeltaTime, owner->position);
}

void CPhysicsBody::LateUpdate() {}

void CPhysicsBody::UpdateCollisions(bool collision) {
  // prevCollision = currCollision;
  // currCollision = collision;
}

void CPhysicsBody::Velocity(glm::vec3 v) {
  // _velocity = v;
}

glm::vec3 CPhysicsBody::Velocity() const {
  // return _velocity;
}

void CPhysicsBody::Acceleration(glm::vec3 a) {
  // _acceleration = a;
}

glm::vec3 CPhysicsBody::Acceleration() const {
  // return _acceleration;
}

void CPhysicsBody::UpdatePositionRef(float deltaTime, glm::vec3& position) {
  // if(prevCollision && currCollision) {
  //   _velocity.x = 0; _velocity.y = 0;
  // }
  // else if (currCollision)
  // {
  //   _velocity.y = -_velocity.y;
  // }
  // else {
  //   _velocity += _acceleration * deltaTime;
  // }
  // position += _velocity * deltaTime;
}