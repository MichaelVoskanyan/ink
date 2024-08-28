#ifndef INK_ENTITY_H
#define INK_ENTITY_H

#include "component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <memory>

class entity_t
{
public:
    template <typename T>
    std::shared_ptr<T> AddComponent()
    {
        static_assert(std::is_base_of<component_t, T>::value, "T must derive from Component");

        for(auto &existingComp : components_)
        {
            if(std::dynamic_pointer_cast<T>(existingComp))
            {
                return std::dynamic_pointer_cast<T>(existingComp);
            }
        }

        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        components_.push_back(newComponent);

        return newComponent;
    }

    template <typename T>
    std::shared_ptr<T> GetComponent()
    {
        static_assert(std::is_base_of<component_t, T>::value, "T must derive from Component");

        for(auto &existing : components_)
        {
            if(std::dynamic_pointer_cast<T>(existing))
            {
                return std::dynamic_pointer_cast<T>(existing);
            }
        }
        return nullptr;
    }

    const int GetID()
    {
        return id_;
    }

    void Init();
    void Start();
    void Update(float deltaTime);
    void LateUpdate();

    /* -- Raw Transform Member Vars -- */
    glm::vec3 position_;
    glm::quat rotation_;
    glm::vec3 scale_;
    float size_;

private:
    std::vector<std::shared_ptr<component_t>> components_;
    static int s_idCounter;
    int id_;
};

#endif
