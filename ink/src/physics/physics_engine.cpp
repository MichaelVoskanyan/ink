#include <physics/physics_engine.h>
#include <iostream>

PhysicsEngine::PhysicsEngine() {}

void PhysicsEngine::add_physics_body(std::shared_ptr<PhysicsBody> body) {
  m_bodies.push_back(body);
}

void PhysicsEngine::remove_physics_body(std::shared_ptr<PhysicsBody> body) {
  for(uint32_t i = 0; i < m_bodies.size(); i++) {
    if(body == m_bodies[i]) {
      m_bodies.erase(m_bodies.begin() + i);
      return;
    }
  }
  std::cerr << "Error: Body not found" << std::endl;
}

void PhysicsEngine::update(float deltaTime) {
  for(auto& body : m_bodies) {
	  body->update_position(deltaTime);
  }
	handle_collisions();
}

void PhysicsEngine::handle_collisions() {
  for(size_t i = 0; i < m_bodies.size(); ++i) {
    for(size_t j = i + 1; j < m_bodies.size(); ++j) {
      if(check_collision(*m_bodies[i], *m_bodies[j])) {
		  resolve_collision(*m_bodies[i], *m_bodies[j]);
      }
    }
  }
}

bool PhysicsEngine::check_collision(const PhysicsBody& body1, const PhysicsBody& body2) {
  glm::vec3 pos1 = body1.position();
  glm::vec3 size1 = body1.size();
  glm::vec3 pos2 = body2.position();
  glm::vec3 size2 = body2.size();

  return (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x && pos1.y < pos2.y + size2.y &&
          pos1.y + size1.y > pos2.y && pos1.z < pos2.z + size2.z && pos1.z + size1.z > pos2.z);
}

void PhysicsEngine::resolve_collision(PhysicsBody& body1, PhysicsBody& body2) {
  // Simple collision resolution: stop both bodies
	body1.velocity(glm::vec3(0.0f));
	body2.velocity(glm::vec3(0.0f));
  std::cout << "Objects collided!" << std::endl;
  // Alternatively, more sophisticated physics could be applied here
}
