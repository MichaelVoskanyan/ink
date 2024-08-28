#include "ecs/components/c_box_collider.h"

#include "ecs/entity.h"

#include <iostream>

void cBoxCollider_t::Init() {}
void cBoxCollider_t::Start() {}
void cBoxCollider_t::Update(float deltaTime) {}
void cBoxCollider_t::LateUpdate() {}

glm::vec3 cBoxCollider_t::GetPosition() const
{
    return this->owner_->position_;
}

glm::vec2 cBoxCollider_t::CheckCollision(cBoxCollider_t a, cBoxCollider_t b)
{
    glm::vec3 posA = a.GetPosition(), posB = b.GetPosition();

    glm::vec2 overlap(0.f, 0.f);

    float checkRight = posA.x + a.width_ / 2 - (posB.x - b.width_ / 2);

    float checkLeft = posB.x + b.width_ / 2 - (posA.x - a.width_ / 2);

    if(checkRight > 0 && checkLeft > 0)
    {
        overlap.x = std::min(checkRight, checkLeft);
    }

    float checkTop = posA.y + a.height_ / 2 - (posB.y - b.height_ / 2);

    float checkBottom = posB.y + b.height_ / 2 - (posA.y - a.height_ / 2);

    if(checkTop > 0 && checkBottom > 0)
    {
        overlap.y = std::min(checkTop, checkBottom);
    }
    return overlap;
}
