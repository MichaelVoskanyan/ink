#ifndef INK_PHYSICSENGINE_H
#define INK_PHYSICSENGINE_H

#include <vector>
#include <memory>
#include "physicsBase.h"

class PhysicsEngine {
public:
    PhysicsEngine();

    void addPhysicsBody(std::shared_ptr<PhysicsBody> body);
    void removePhysicsBody(std::shared_ptr<PhysicsBody> body);

    void update(float deltaTime);
    void handleCollisions();

private:
    std::vector<std::shared_ptr<PhysicsBody>> _bodies;
    bool checkCollision(const PhysicsBody& body1, const PhysicsBody& body2);
    void resolveCollision(PhysicsBody& body1, PhysicsBody& body2);
};

#endif // INK_PHYSICSENGINE_H