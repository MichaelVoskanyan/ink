#include <physics/physics_engine.h>
#include <iostream>

PhysicsEngine::PhysicsEngine() {}

void PhysicsEngine::AddPhysicsBody(std::shared_ptr<PhysicsBody> body) {
  _bodies.push_back(body);
}

void PhysicsEngine::RemovePhysicsBody(std::shared_ptr<PhysicsBody> body) {
  for(uint32_t i = 0; i < _bodies.size(); i++) {
    if(body == _bodies[i]) {
      _bodies.erase(_bodies.begin() + i);
      return;
    }
  }
  std::cerr << "Error: Body not found" << std::endl;
}

void PhysicsEngine::Update(float deltaTime) {
  for(auto& body : _bodies) {
    body->UpdatePosition(deltaTime);
  }
  HandleCollisions();
}

void PhysicsEngine::HandleCollisions() {
  for(size_t i = 0; i < _bodies.size(); ++i) {
    for(size_t j = i + 1; j < _bodies.size(); ++j) {
      if(CheckCollision(*_bodies[i], *_bodies[j])) {
        ResolveCollision(*_bodies[i], *_bodies[j]);
      }
    }
  }
}

bool PhysicsEngine::CheckCollision(const PhysicsBody& body1, const PhysicsBody& body2) {
  glm::vec3 pos1 = body1.Position();
  glm::vec3 size1 = body1.Size();
  glm::vec3 pos2 = body2.Position();
  glm::vec3 size2 = body2.Size();

  return (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x && pos1.y < pos2.y + size2.y &&
          pos1.y + size1.y > pos2.y && pos1.z < pos2.z + size2.z && pos1.z + size1.z > pos2.z);
}

void PhysicsEngine::ResolveCollision(PhysicsBody& body1, PhysicsBody& body2) {
  // Simple collision resolution: stop both bodies
  body1.Velocity(glm::vec3(0.0f));
  body2.Velocity(glm::vec3(0.0f));
  std::cout << "Objects collided!" << std::endl;
  // Alternatively, more sophisticated physics could be applied here
}
