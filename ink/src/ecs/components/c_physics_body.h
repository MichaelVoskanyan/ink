#pragma once

#include "ecs/component.h"

class C_PhysicsBody : public Component
{
public:
    C_PhysicsBody(Entity *owner) :Component(owner) {}

    void init() override;
    void start() override;
    void update(float deltaTime) override;
    void late_update() override;
    // PhysicsBody(glm::vec3 position, glm::vec3 size);

    void velocity(glm::vec3 v);
    glm::vec3 velocity() const;

    void acceleration(glm::vec3 a);
    glm::vec3 acceleration() const;

    void update_position_ref(float deltaTime, glm::vec3 &position);

private:
    glm::vec3 m_acceleration;
    glm::vec3 m_velocity;
    const float GRAVITY = 1.5f; // acceleration due to gravity
};
