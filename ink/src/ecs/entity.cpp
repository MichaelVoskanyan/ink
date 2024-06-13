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

void Entity::LateUpdate() {
  for(int i = components.size() - 1; i >= 0; i--) {
    components[i]->LateUpdate();
  }
}
