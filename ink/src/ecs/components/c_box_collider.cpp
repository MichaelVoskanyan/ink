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

bool C_BoxCollider::check_collision(C_BoxCollider a, C_BoxCollider b)
{
    glm::vec3 posA = a.get_pos(), posB = b.get_pos();

    bool checkARight =
        (posA.x + a.m_width / 2 >= posB.x - b.m_width / 2) && (posA.x + a.m_width / 2 <= posB.x + b.m_width / 2);
    bool checkALeft =
        (posA.x - a.m_width / 2 <= posB.x + b.m_width / 2) && (posA.x - a.m_width / 2 >= posB.x - b.m_width / 2);

    bool checkX = checkARight || checkALeft;

    if(!checkX)
    {
        return false;
    }

    bool checkATop =
        (posA.y + a.m_height / 2 >= posB.y - b.m_height / 2) && (posA.y + a.m_height / 2 <= posB.y + b.m_height / 2);
    bool checkABottom =
        (posA.y - a.m_width / 2 <= posB.y + b.m_height / 2) && (posA.y - a.m_width / 2 >= posB.y - b.m_height / 2);

    bool checkY = checkATop || checkABottom;

    return checkX && checkY;
}
