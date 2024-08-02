#pragma once

#include "ecs/component.h"

class C_CharacterController : public Component
{
public:
    C_CharacterController(Entity *owner) :Component(owner) {}

    void init();
    void start();
    void update(float deltaTime);
    void late_update();

private:
    void process_keyboard(float deltaTime);
};
