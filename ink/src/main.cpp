#include "ink.h"

#include <iostream>
#include <vector>
#include <memory>

class Ink : public Application {
public:
  Ink() {
    _window = std::unique_ptr<Window>(Window::Create());

    Start();
  }

  std::vector<std::shared_ptr<CBoxCollider>> colliders;

  std::shared_ptr<Entity> player;

  std::shared_ptr<CBoxCollider> playerCol;
  std::shared_ptr<CBoxCollider> blockCol;

  void Start() {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("/shaders/tri.vs", "/shaders/tri.fs");
    shader->use();

    // h_Rend->setActiveShaderHandle(shader);

    auto camera = Camera::GetInstance();

    std::vector<float> verts1 = {-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

    std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};

    player = std::make_shared<Entity>();
    std::shared_ptr<CRenderObject> ro = player->AddComponent<CRenderObject>();
    std::shared_ptr<CCharacterController> cc = player->AddComponent<CCharacterController>();
    std::shared_ptr<CPhysicsBody> phyicsBody = player->AddComponent<CPhysicsBody>();
    playerCol = player->AddComponent<CBoxCollider>();

    std::shared_ptr<Entity> block = std::make_shared<Entity>();
    std::shared_ptr<CRenderObject> blockRend = block->AddComponent<CRenderObject>();
    blockCol = block->AddComponent<CBoxCollider>();

    ro->vertices = verts1;
    ro->indices = physicsinds;
    ro->SetShader(shader);

    blockRend->vertices = verts1;
    blockRend->indices = physicsinds;
    blockRend->SetShader(shader);

    player->position = glm::vec3(0.f, 0.f, 0.f);
    player->rotation = glm::vec3(0.f);
    player->scale = glm::vec3(1.f);

    block->position = glm::vec3(0.f, -1.25f, 0.f);
    block->rotation = glm::vec3(0.f);
    block->scale = glm::vec3(1.f);

    playerCol->m_width = 1;
    playerCol->m_height = 1;
    blockCol->m_width = 1;
    blockCol->m_height = 1;

    _entities.push_back(player);
    _entities.push_back(block);

    for(auto& e : _entities) {
      e->Init();
      e->Start();
    }
  }

  void Run() {

    while(!glfwWindowShouldClose(_window->GetGlfwWindow())) {
      glClear(GL_COLOR_BUFFER_BIT);
      float currentFrame = (float)glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      for(auto& e : _entities) {
        e->Update(deltaTime);
      }

      for(auto& e : _entities) {
        e->LateUpdate();
      }

      if(CBoxCollider::CheckCollision(*playerCol, *blockCol)) {
        std::shared_ptr<CPhysicsBody> playerPhys = player->GetComponent<CPhysicsBody>();
        glm::vec3 currVel = playerPhys->Velocity();
        currVel.y = 0.f;
        playerPhys->Velocity(currVel);
        std::cout << "Collision\n";
      }

      glfwPollEvents();
      glfwSwapBuffers(_window->GetGlfwWindow());
    }
  }
};

int main(int argc, char** argv) {
  auto ink = new Ink();

  ink->Run();
  glfwTerminate();
  return 0;
}
