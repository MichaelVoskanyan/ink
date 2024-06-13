#pragma once

#include "ecs/component.h"

class CCharacterController : public Component {
public:
  CCharacterController(Entity* owner) : Component(owner) {}

  void Init();
  void Start();
  void Update(float deltaTime);
  void LateUpdate();

private:
  void ProcessKeyboard(float deltaTime);
};
