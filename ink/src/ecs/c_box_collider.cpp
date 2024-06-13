#include "ecs/c_box_collider.h"

#include "ecs/entity.h"

#include <iostream>

void CBoxCollider::Init() {}
void CBoxCollider::Start() {}
void CBoxCollider::Update(float deltaTime) {}
void CBoxCollider::PhysicsUpdate(float fixedDeltaTime) {}
void CBoxCollider::LateUpdate() {}

glm::vec3 CBoxCollider::GetPos() const {
  return this->owner->position;
}

bool CBoxCollider::CheckCollision(CBoxCollider a, CBoxCollider b) {
  glm::vec3 posA = a.GetPos(), posB = b.GetPos();

  bool checkARight =
      (posA.x + a.m_width / 2 >= posB.x - b.m_width / 2) && (posA.x + a.m_width / 2 <= posB.x + b.m_width / 2);
  bool checkALeft =
      (posA.x - a.m_width / 2 <= posB.x + b.m_width / 2) && (posA.x - a.m_width / 2 >= posB.x - b.m_width / 2);

  bool checkX = checkARight || checkALeft;

  if(!checkX) {
    return false;
  }

  bool checkATop =
      (posA.y + a.m_height / 2 >= posB.y - b.m_height / 2) && (posA.y + a.m_height / 2 <= posB.y + b.m_height / 2);
  bool checkABottom =
      (posA.y - a.m_width / 2 <= posB.y + b.m_height / 2) && (posA.y - a.m_width / 2 >= posB.y - b.m_height / 2);

  bool checkY = checkATop || checkABottom;

  return checkX && checkY;
}
