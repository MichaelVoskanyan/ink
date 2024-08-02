#include <ecs/components/c_character_controller.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>

void C_CharacterController::init() {}

void C_CharacterController::start() {}

void C_CharacterController::update(float deltaTime)
{
	process_keyboard(deltaTime);
}

void C_CharacterController::late_update() {}

void C_CharacterController::process_keyboard(float deltaTime)
{
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
    {
		m_owner->m_position.y += 5.f * deltaTime;
    }
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
    {
		m_owner->m_position.y -= 5.f * deltaTime;
    }
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
    {
		m_owner->m_position.x += 5.f * deltaTime;
    }
    if(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
    {
		m_owner->m_position.x -= 5.f * deltaTime;
    }
}
