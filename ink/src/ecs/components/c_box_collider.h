#pragma once

#include "ecs/component.h"

class cBoxCollider_t : public component_t
{
public:
    cBoxCollider_t(entity_t *owner) : component_t(owner) {}

    void Init() override;
    void Start() override;
    void Update(float deltaTime) override;
    void LateUpdate() override;

    glm::vec3 GetPosition() const;

    static glm::vec2 CheckCollision(cBoxCollider_t a, cBoxCollider_t b); // AABB collisions

public:
    float width_, height_;
};
