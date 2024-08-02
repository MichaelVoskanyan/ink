#include <ecs/components/c_physics_body.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>
#include <iostream>

void C_PhysicsBody::init()
{
	m_acceleration = glm::vec3(0.0f, -GRAVITY, 0.0f);
	m_velocity = glm::vec3(0.0f);
}

void C_PhysicsBody::start() {}

void C_PhysicsBody::update(float deltaTime)
{
	update_position_ref(deltaTime, m_owner->m_position);
}

void C_PhysicsBody::late_update() {}

void C_PhysicsBody::velocity(glm::vec3 v)
{
	m_velocity = v;
}

glm::vec3 C_PhysicsBody::velocity() const
{
    return m_velocity;
}

void C_PhysicsBody::acceleration(glm::vec3 a)
{
	m_acceleration = a;
}

glm::vec3 C_PhysicsBody::acceleration() const
{
    return m_acceleration;
}

void C_PhysicsBody::update_position_ref(float deltaTime, glm::vec3 &position)
{
	m_velocity += m_acceleration * deltaTime;
    position += m_velocity * deltaTime;
    // std::cout << "Accel: " << _acceleration.x << ", " << _acceleration.y << std::endl;
    // std::cout << "Velocity: " << _velocity.x << ", " << _velocity.y << std::endl;
    // std::cout << "Position: " << position.x << ", " << position.y << std::endl;
}