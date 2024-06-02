#include <physics/physicsBase.h>

PhysicsBody::PhysicsBody(glm::vec3 position, glm::vec3 size)
    : _position(position), _size(size) {
        _acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f);
        _velocity = glm::vec3(0.0f);
    }

void PhysicsBody::velocity(glm::vec3 v) {
    _velocity = v;
}

glm::vec3 PhysicsBody::velocity() const {
    return _velocity;
}

void PhysicsBody::acceleration(glm::vec3 a){
    _acceleration = a;
}

glm::vec3 PhysicsBody::acceleration() const {
    return _acceleration;
}

glm::vec3 PhysicsBody::position() const {
    return _position;
}

glm::vec3 PhysicsBody::size() const {
    return _size;
}


void PhysicsBody::setPosition(glm::vec3 pos) {
    _position = pos;
}

void PhysicsBody::updatePosition(float deltaTime) {
    // Update velocity
    _velocity += _acceleration * deltaTime;

    // Update position
    _position += _velocity * deltaTime;
}