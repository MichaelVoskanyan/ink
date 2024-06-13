#pragma once

#include "component.h"

class CCharacterController : public Component {
public:
  CCharacterController(Entity* owner) : Component(owner) {}

  void Init();
  void Start();
  void Update(float deltaTime);
  void PhysicsUpdate(float fixedDeltaTime);
  void LateUpdate();

private:
  void ProcessKeyboard(float deltaTime);
};
