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

class physicsBody_t {
private:
  glm::vec3 acceleration_;
  glm::vec3 velocity_;
  glm::vec3 position_;           // reference to world position of the object
  glm::vec3 size_;               // bounding box for collision detection
  const int kFramesPerSec_ = 60; // 60 FPS for time deltas
  const float kGravity_ = 0.1f;    // acceleration due to gravity

public:
  physicsBody_t();
  physicsBody_t(glm::vec3 position, glm::vec3 size);

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
