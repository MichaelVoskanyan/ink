#include <physics/physicsEngine.h>
#include <iostream>

PhysicsEngine::PhysicsEngine() {}

void PhysicsEngine::addPhysicsBody(std::shared_ptr<PhysicsBody> body) {
    _bodies.push_back(body);
}

void PhysicsEngine::removePhysicsBody(std::shared_ptr<PhysicsBody> body) {
    for(uint32_t i = 0; i < _bodies.size(); i++) {
        if(body == _bodies[i]) {
            _bodies.erase(_bodies.begin() + i);
            return;
        }
    }
    std::cerr << "Error: Body not found" << std::endl;
}

void PhysicsEngine::update(float deltaTime) {
    for (auto& body : _bodies) {
        body->updatePosition(deltaTime);
    }
    handleCollisions();
}

void PhysicsEngine::handleCollisions() {
    for (size_t i = 0; i < _bodies.size(); ++i) {
        for (size_t j = i + 1; j < _bodies.size(); ++j) {
            if (checkCollision(*_bodies[i], *_bodies[j])) {
                resolveCollision(*_bodies[i], *_bodies[j]);
            }
        }
    }
}

bool PhysicsEngine::checkCollision(const PhysicsBody& body1, const PhysicsBody& body2) {
    glm::vec3 pos1 = body1.position();
    glm::vec3 size1 = body1.size();
    glm::vec3 pos2 = body2.position();
    glm::vec3 size2 = body2.size();

    return (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x &&
            pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y &&
            pos1.z < pos2.z + size2.z && pos1.z + size1.z > pos2.z);
}

void PhysicsEngine::resolveCollision(PhysicsBody& body1, PhysicsBody& body2) {
    // Simple collision resolution: stop both bodies
    body1.velocity(glm::vec3(0.0f));
    body2.velocity(glm::vec3(0.0f));
    std::cout << "Objects collided!" << std::endl;
    // Alternatively, more sophisticated physics could be applied here
}
