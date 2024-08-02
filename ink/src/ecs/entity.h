#ifndef INK_ENTITY_H
#define INK_ENTITY_H

#include "component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <memory>

class Entity
{
public:
    template <typename T>
    std::shared_ptr<T> add_component()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for(auto &existingComp : m_components)
        {
            if(std::dynamic_pointer_cast<T>(existingComp))
            {
                return std::dynamic_pointer_cast<T>(existingComp);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        m_components.push_back(newComponent);

        return newComponent;
    }

    template <typename T>
    std::shared_ptr<T> get_component()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for(auto &existing : m_components)
        {
            if(std::dynamic_pointer_cast<T>(existing))
            {
                return std::dynamic_pointer_cast<T>(existing);
            }
        }
        return nullptr;
    }

private:
    std::vector<std::shared_ptr<Component>> m_components;

public:
    void init();
    void start();
    void update(float deltaTime);
    void late_update();

    /* -- Raw Transform Member Vars -- */
public:
    glm::vec3 m_position;
    glm::quat m_rotation;
    glm::vec3 m_scale;
    float m_size;
};

#endif