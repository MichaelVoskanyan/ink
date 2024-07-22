#pragma once

#include "ecs/component.h"
#include <ecs/components/c_physics_body.h>

class CCharacterController : public Component {
public:
  CCharacterController(Entity* owner) : Component(owner) {}

  void Init();
  void Start();
  void Update(float deltaTime);
  void LateUpdate();
  bool spaceWasPressed;
  std::shared_ptr<CPhysicsBody> body;

private:
  void ProcessKeyboard(float deltaTime);
};
