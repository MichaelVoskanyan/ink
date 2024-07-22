#include <ecs/c_physics_dynamic_body.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>
#include <iostream>

void CPhysicsDynamicBody::Init() {
  _acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f);
  _velocity = glm::vec3(0.0f);
  prevCollision = false;
  currCollision = false;
  stopped = false;
}

void CPhysicsDynamicBody::Start() {}

void CPhysicsDynamicBody::Update(float deltaTime) {}

void CPhysicsDynamicBody::PhysicsUpdate(float fixedDeltaTime) {
  UpdatePositionRef(fixedDeltaTime, owner->position);
}

void CPhysicsDynamicBody::LateUpdate() {}

void CPhysicsDynamicBody::UpdateCollisions(bool collision) {
  currCollision = collision;
  UpdatePositionRef(1.0f / 120.f, owner->position);
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

// TODO: Fix this. Sometimes objects randomly stop after falling when they should bounce instead
void CPhysicsDynamicBody::UpdatePositionRef(float deltaTime, glm::vec3& position) {
    // Update velocity with acceleration

    // Handle collision logic
    if (currCollision) {
      if(!stopped) {
        if (fabs(_velocity.y) < velocity_threshold) {
          std::cout << "Stopped! Current Velocity = " << _velocity.y << std::endl;
          _velocity.y = 0; 
          stopped = true;
        } else {
            _velocity.y = -0.9f * _velocity.y;
            std::cout << "Collision detected: Current Velocity = " << _velocity.y << std::endl;
        }
      }
    }
    else {
      stopped = false;
      // Update position
      _velocity += _acceleration * deltaTime;

    }
    position += _velocity * deltaTime;
    // Output current velocity and acceleration for debugging
    std::cout << "Current Position: " << position.y << std::endl;
    std::cout << "Current Velocity: " << _velocity.y << std::endl;
    std::cout << "Current Acceleration: " << _acceleration.y << std::endl;
}
