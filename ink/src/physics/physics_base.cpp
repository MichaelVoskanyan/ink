#include <physics/physics_base.h>
#include <iostream>

physicsBody_t::physicsBody_t(glm::vec3 position, glm::vec3 size) :position_(position), size_(size) {
	acceleration_ = glm::vec3(0.0f, -kGravity_, 0.0f);
	velocity_ = glm::vec3(0.0f);
}

void physicsBody_t::Velocity(glm::vec3 v) {
	velocity_ = v;
}

glm::vec3 physicsBody_t::Velocity() const {
  return velocity_;
}

void physicsBody_t::Acceleration(glm::vec3 a) {
	acceleration_ = a;
}

glm::vec3 physicsBody_t::Acceleration() const {
  return acceleration_;
}

glm::vec3 physicsBody_t::Position() const {
  return position_;
}

glm::vec3 physicsBody_t::Size() const {
  return size_;
}

void physicsBody_t::SetPosition(glm::vec3 pos) {
	position_ = pos;
}

void physicsBody_t::UpdatePosition(float deltaTime) {
  // Update velocity
  velocity_ += acceleration_ * deltaTime;

  // Update position
  position_ += velocity_ * deltaTime;
}

void physicsBody_t::UpdatePositionRef(float deltaTime, glm::vec3& position) {
	velocity_ += acceleration_ * deltaTime;
  position += velocity_ * deltaTime;
  std::cout << "Accel: " << acceleration_.x << ", " << acceleration_.y << std::endl;
  std::cout << "velocity: " << velocity_.x << ", " << velocity_.y << std::endl;
  std::cout << "position: " << position.x << ", " << position.y << std::endl;
}
