#ifndef INK_PHYSICSBASE_H
#define INK_PHYSICSBASE_H

#include <glm/glm.hpp>

// Class basically exists to handle the translation of acceleration & velocity
// into changes in position.
// position = d(velocity) /dt
// velocity = d(acceleration) / dt

// In other words
// velocity = 1/2 acceleration ^ 2
// position = 1/2 velocity ^ 2 = 1/6 acceleration ^ 3

// Every game object has a defined world position. Position is influenced by
// velocity and acceleration forces. Should be able to set velocity or
// acceleration in code.

class PhysicsBody {
private:
  glm::vec3 _acceleration;
  glm::vec3 _velocity;
  glm::vec3 _position;           // reference to world position of the object
  glm::vec3 _size;               // bounding box for collision detection
  const int FRAMES_PER_SEC = 60; // 60 FPS for time deltas
  const float GRAVITY = 0.1f;    // acceleration due to gravity

public:
  PhysicsBody();
  PhysicsBody(glm::vec3 position, glm::vec3 size);

  void Velocity(glm::vec3 v);
  glm::vec3 Velocity() const;

  void Acceleration(glm::vec3 a);
  glm::vec3 Acceleration() const;
  glm::vec3 Size() const;
  glm::vec3 Position() const;

  void SetPosition(glm::vec3 pos);
  void UpdatePosition(float deltaTime);
  void UpdatePositionRef(float deltaTime, glm::vec3 &position);
  void UpdateVelocity();
};

#endif // INK_PHYSICSBASE_H
