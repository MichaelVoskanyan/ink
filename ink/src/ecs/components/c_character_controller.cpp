#include <ecs/components/c_character_controller.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>

void CCharacterController::Init() {}

void CCharacterController::Start() {}

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
}
