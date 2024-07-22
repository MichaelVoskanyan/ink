#include <ecs/components/c_character_controller.h>
#include <ecs/components/c_physics_body.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

void CCharacterController::Init() {
  spaceWasPressed = false;
}

void CCharacterController::Start() {
  body = owner->GetComponent<CPhysicsBody>();
}

void CCharacterController::Update(float deltaTime) {
  ProcessKeyboard(deltaTime);
}

void CCharacterController::LateUpdate() {}

void CCharacterController::ProcessKeyboard(float deltaTime) {
  if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
    owner->position.y += 5.f * deltaTime;
  }
  if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
    owner->position.y -= 5.f * deltaTime;
  }
  if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
    owner->position.x += 5.f * deltaTime;
  }
  if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
    owner->position.x -= 5.f * deltaTime;
  }
  bool spaceIsPressed = glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS;
  if (spaceIsPressed && !spaceWasPressed) {
    glm::vec3 currVelocity = body->Velocity();
    body->Velocity(currVelocity + glm::vec3(0.f, 2.f, 0.f));
  }
  spaceWasPressed = spaceIsPressed;
}