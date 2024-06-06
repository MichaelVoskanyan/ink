#ifndef INK_ENTITY_H
#define INK_ENTITY_H

#include <vector>
#include <memory>
#include "component.h"

class Entity {
public:
  template <typename T>
  std::shared_ptr<T> AddComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    for(auto& existingComp : components) {
      if(std::dynamic_pointer_cast<T>(existingComp)) {
        return std::dynamic_pointer_cast<T>(existingComp);
      }
    }

    std::shared_ptr<T> newComponent = std::make_shared<T>(this);
    components.push_back(newComponent);

    return newComponent;
  }

  template <typename T>
  std::shared_ptr<T> GetComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

    for(auto& existing : components) {
      if(std::dynamic_pointer_cast<T>(existing)) {
        return std::dynamic_pointer_cast<T>(existing);
      }
    }
    return nullptr;
  }

private:
  std::vector<std::shared_ptr<Component>> components;

public:
  void Init();
  void Start();
  void Update(float deltaTime);
  void PhysicsUpdate(float fixedDeltaTime);
  void LateUpdate(float deltaTime);

  /* -- Raw Tranform Member Vars -- */
public:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};

#endif