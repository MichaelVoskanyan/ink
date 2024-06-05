#include <physics/physics_base.h>
#include <iostream>

PhysicsBody::PhysicsBody(glm::vec3 position, glm::vec3 size) : _position(position), _size(size) {
  _acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f);
  _velocity = glm::vec3(0.0f);
}

void PhysicsBody::Velocity(glm::vec3 v) {
  _velocity = v;
}

glm::vec3 PhysicsBody::Velocity() const {
  return _velocity;
}

void PhysicsBody::Acceleration(glm::vec3 a) {
  _acceleration = a;
}

glm::vec3 PhysicsBody::Acceleration() const {
  return _acceleration;
}

glm::vec3 PhysicsBody::Position() const {
  return _position;
}

glm::vec3 PhysicsBody::Size() const {
  return _size;
}

void PhysicsBody::SetPosition(glm::vec3 pos) {
  _position = pos;
}

void PhysicsBody::UpdatePosition(float deltaTime) {
  // Update velocity
  _velocity += _acceleration * deltaTime;

  // Update position
  _position += _velocity * deltaTime;
}

void PhysicsBody::UpdatePositionRef(float deltaTime, glm::vec3& position) {
  _velocity += _acceleration * deltaTime;
  position += _velocity * deltaTime;
  std::cout << "Accel: " << _acceleration.x << ", " << _acceleration.y << std::endl;
  std::cout << "Velocity: " << _velocity.x << ", " << _velocity.y << std::endl;
  std::cout << "Position: " << position.x << ", " << position.y << std::endl;
}