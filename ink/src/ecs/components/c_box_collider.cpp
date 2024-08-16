#include "ecs/components/c_box_collider.h"

#include "ecs/entity.h"

#include <iostream>

void C_BoxCollider::init() {}
void C_BoxCollider::start() {}
void C_BoxCollider::update(float deltaTime) {}
void C_BoxCollider::late_update() {}

glm::vec3 C_BoxCollider::get_pos() const
{
    return this->m_owner->m_position;
}

glm::vec2 C_BoxCollider::check_collision(C_BoxCollider a, C_BoxCollider b)
{
    glm::vec3 posA = a.get_pos(), posB = b.get_pos();

    glm::vec2 overlap(0.f, 0.f);

    float checkRight = posA.x + a.m_width / 2 - (posB.x - b.m_width / 2);

    float checkLeft = posB.x + b.m_width / 2 - (posA.x - a.m_width / 2);

    if(checkRight > 0 && checkLeft > 0)
    {
        overlap.x = std::min(checkRight, checkLeft);
    }

    float checkTop = posA.y + a.m_height / 2 - (posB.y - b.m_height / 2);

    float checkBottom = posB.y + b.m_height / 2 - (posA.y - a.m_height / 2);

    if(checkTop > 0 && checkBottom > 0)
    {
        overlap.y = std::min(checkTop, checkBottom);
    }
    return overlap;
}
