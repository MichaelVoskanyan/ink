#pragma once

#include "ecs/component.h"

class cPhysicsBody_t : public component_t
{
public:
    cPhysicsBody_t(entity_t *owner) :component_t(owner) {}

    void Init() override;
    void Start() override;
    void Update(float deltaTime) override;
    void LateUpdate() override;
    // PhysicsBody(glm::vec3 position, glm::vec3 size);

    void Velocity(glm::vec3 v);
    glm::vec3 Velocity() const;

    void Acceleration(glm::vec3 a);
    glm::vec3 Acceleration() const;

    void UpdatePositionRef(float deltaTime, glm::vec3 &position);

private:
    glm::vec3 acceleration_;
    glm::vec3 velocity_;
    const float kGravity_ = 1.5f; // acceleration due to gravity
};
