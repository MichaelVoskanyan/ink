#pragma once

#include "ecs/component.h"

class C_BoxCollider : public Component
{
public:
    C_BoxCollider(Entity *owner) : Component(owner) {}

    void init() override;
    void start() override;
    void update(float deltaTime) override;
    void late_update() override;

    glm::vec3 get_pos() const;

    static glm::vec2 check_collision(C_BoxCollider a, C_BoxCollider b); // AABB collisions

public:
    float m_width, m_height;
};
