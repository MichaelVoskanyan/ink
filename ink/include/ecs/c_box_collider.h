#pragma once

#include "ecs/component.h"

class CBoxCollider : public Component {
public:
  CBoxCollider(Entity* owner) : Component(owner) {}

  void Init() override;
  void Start() override;
  void Update(float deltaTime) override;
  void PhysicsUpdate(float fixedDeltaTime) override;
  void LateUpdate() override;

  glm::vec3 GetPos() const;

  static bool CheckCollision(CBoxCollider a, CBoxCollider b); // AABB collisions

public:
  float m_width, m_height;
};
