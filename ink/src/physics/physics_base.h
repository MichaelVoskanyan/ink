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
  glm::vec3 m_acceleration;
  glm::vec3 m_velocity;
  glm::vec3 m_position;           // reference to world position of the object
  glm::vec3 m_size;               // bounding box for collision detection
  const int FRAMES_PER_SEC = 60; // 60 FPS for time deltas
  const float GRAVITY = 0.1f;    // acceleration due to gravity

public:
  PhysicsBody();
  PhysicsBody(glm::vec3 position, glm::vec3 size);

  void velocity(glm::vec3 v);
  glm::vec3 velocity() const;

  void acceleration(glm::vec3 a);
  glm::vec3 acceleration() const;
  glm::vec3 size() const;
  glm::vec3 position() const;

  void set_position(glm::vec3 pos);
  void update_position(float deltaTime);
  void update_position_ref(float deltaTime, glm::vec3 &position);
  void update_velocity();
};

#endif // INK_PHYSICSBASE_H
