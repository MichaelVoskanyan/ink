#include <physics/physics_base.h>
#include <iostream>

PhysicsBody::PhysicsBody(glm::vec3 position, glm::vec3 size) :m_position(position), m_size(size) {
	m_acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f);
	m_velocity = glm::vec3(0.0f);
}

void PhysicsBody::velocity(glm::vec3 v) {
	m_velocity = v;
}

glm::vec3 PhysicsBody::velocity() const {
  return m_velocity;
}

void PhysicsBody::acceleration(glm::vec3 a) {
	m_acceleration = a;
}

glm::vec3 PhysicsBody::acceleration() const {
  return m_acceleration;
}

glm::vec3 PhysicsBody::position() const {
  return m_position;
}

glm::vec3 PhysicsBody::size() const {
  return m_size;
}

void PhysicsBody::set_position(glm::vec3 pos) {
	m_position = pos;
}

void PhysicsBody::update_position(float deltaTime) {
  // Update velocity
  m_velocity += m_acceleration * deltaTime;

  // Update position
  m_position += m_velocity * deltaTime;
}

void PhysicsBody::update_position_ref(float deltaTime, glm::vec3& position) {
	m_velocity += m_acceleration * deltaTime;
  position += m_velocity * deltaTime;
  std::cout << "Accel: " << m_acceleration.x << ", " << m_acceleration.y << std::endl;
  std::cout << "velocity: " << m_velocity.x << ", " << m_velocity.y << std::endl;
  std::cout << "position: " << position.x << ", " << position.y << std::endl;
}