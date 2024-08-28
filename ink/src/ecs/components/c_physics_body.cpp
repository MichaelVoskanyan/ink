#include <ecs/components/c_physics_body.h>
#include <ecs/entity.h>
#include <GLFW/glfw3.h>
#include <iostream>

void cPhysicsBody_t::Init()
{
	acceleration_ = glm::vec3(0.0f, -kGravity_, 0.0f);
	velocity_ = glm::vec3(0.0f);
}

void cPhysicsBody_t::Start() {}

void cPhysicsBody_t::Update(float deltaTime)
{
	UpdatePositionRef(deltaTime, owner_->position_);
}

void cPhysicsBody_t::LateUpdate() {}

void cPhysicsBody_t::Velocity(glm::vec3 v)
{
	velocity_ = v;
}

glm::vec3 cPhysicsBody_t::Velocity() const
{
    return velocity_;
}

void cPhysicsBody_t::Acceleration(glm::vec3 a)
{
	acceleration_ = a;
}

glm::vec3 cPhysicsBody_t::Acceleration() const
{
    return acceleration_;
}

void cPhysicsBody_t::UpdatePositionRef(float deltaTime, glm::vec3 &position)
{
	velocity_ += acceleration_ * deltaTime;
    position += velocity_ * deltaTime;
    // std::cout << "Accel: " << _acceleration.x << ", " << _acceleration.y << std::endl;
    // std::cout << "Velocity: " << _velocity.x << ", " << _velocity.y << std::endl;
    // std::cout << "Position: " << position.x << ", " << position.y << std::endl;
}
