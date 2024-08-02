#include <ecs/entity.h>

void Entity::init()
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->init();
    }
}

void Entity::start()
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->start();
    }
}

void Entity::update(float deltaTime)
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
        m_components[i]->update(deltaTime);
    }
}

void Entity::late_update()
{
    for(int i = m_components.size() - 1; i >= 0; i--)
    {
		m_components[i]->late_update();
    }
}
