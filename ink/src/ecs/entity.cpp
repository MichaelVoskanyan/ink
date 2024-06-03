#include <ecs/entity.h>

void Entity::init() {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->init();
  }
}

void Entity::start() {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->start();
  }
}

void Entity::update(float deltaTime) {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->update(deltaTime);
  }
}

void Entity::physicsUpdate(float fixedDeltaTime) {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->physicsUpdate(fixedDeltaTime);
  }
}

void Entity::lateUpdate(float deltaTime) {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->lateUpdate(deltaTime);
  }
}
