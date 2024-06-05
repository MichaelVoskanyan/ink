#include <ecs/entity.h>

void Entity::Init() {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->Init();
  }
}

void Entity::Start() {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->Start();
  }
}

void Entity::Update(float deltaTime) {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->Update(deltaTime);
  }
}

void Entity::PhysicsUpdate(float fixedDeltaTime) {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->PhysicsUpdate(fixedDeltaTime);
  }
}

void Entity::LateUpdate(float deltaTime) {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->LateUpdate(deltaTime);
  }
}
