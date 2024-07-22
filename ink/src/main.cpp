#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/render_object.h>
#include <renderer/vertex_array.h>

#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/c_render_object.h>
#include <ecs/c_character_controller.h>
#include <ecs/c_physics_body.h>
#include <ecs/c_physics_dynamic_body.h>
#include <ecs/c_physics_static_body.h>
#include <ecs/c_box_collider.h>

#include <core/camera.h>
#include <core/shader.h>
#include <core/window.h>

#include <core/application.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <memory>

class Ink : public Application {
public:
  Ink() {
    m_Window = std::unique_ptr<Window>(Window::Create());

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
    std::shared_ptr<CPhysicsDynamicBody> physicsBody = player->AddComponent<CPhysicsDynamicBody>();
    playerCol = player->AddComponent<CBoxCollider>();

    std::shared_ptr<Entity> block = std::make_shared<Entity>();
    std::shared_ptr<CRenderObject> blockRend = block->AddComponent<CRenderObject>();
    std::shared_ptr<CPhysicsStaticBody> blockPhysicsBody = block->AddComponent<CPhysicsStaticBody>();
    // blockPhysicsBody->Velocity(glm::vec3(0.f, 5.0f, 0.f));
    blockCol = block->AddComponent<CBoxCollider>();

    ro->vertices = verts1;
    ro->indices = physicsinds;
    ro->SetShader(shader);

    blockRend->vertices = verts1;
    blockRend->indices = physicsinds;
    blockRend->SetShader(shader);

    player->position = glm::vec3(0.f, 1.25f, 0.f);
    player->rotation = glm::vec3(0.f);
    player->scale = glm::vec3(1.f);

    block->position = glm::vec3(0.f, -0.25f, 0.f);
    block->rotation = glm::vec3(0.f);
    block->scale = glm::vec3(1.f);

    playerCol->m_width = 1;
    playerCol->m_height = 1;
    blockCol->m_width = 1;
    blockCol->m_height = 1;

    entities.push_back(player);
    entities.push_back(block);

    for(auto& e : entities) {
      e->Init();
      e->Start();
    }
  }

  void Run() {

    while(!glfwWindowShouldClose(m_Window->GetGlfwWindow())) {
      glClear(GL_COLOR_BUFFER_BIT);
      float currentFrame = (float)glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;
      for(uint32_t i = 0; i < entities.size() - 1; i++) {
        std::shared_ptr<CBoxCollider> bodyCollider1 = entities[i]->GetComponent<CBoxCollider>();
        std::shared_ptr<CPhysicsBody> bodyPhys1 = entities[i]->GetComponent<CPhysicsBody>();

        auto dynamicBody1 = std::dynamic_pointer_cast<CPhysicsDynamicBody>(bodyPhys1);
        auto staticBody1 = std::dynamic_pointer_cast<CPhysicsStaticBody>(bodyPhys1);

        // TODO: Clean this up
        for(uint32_t j = i + 1; j < entities.size(); j++) {
            std::shared_ptr<CBoxCollider> bodyCollider2 = entities[j]->GetComponent<CBoxCollider>();
            std::shared_ptr<CPhysicsBody> bodyPhys2 = entities[j]->GetComponent<CPhysicsBody>();

            auto dynamicBody2 = std::dynamic_pointer_cast<CPhysicsDynamicBody>(bodyPhys2);
            auto staticBody2 = std::dynamic_pointer_cast<CPhysicsStaticBody>(bodyPhys2);
            if(CBoxCollider::CheckCollision(*bodyCollider1, *bodyCollider2)) {
                if (dynamicBody1) dynamicBody1->UpdateCollisions(true);
                else if (staticBody1) staticBody1->UpdateCollisions(true);

                if (dynamicBody2) dynamicBody2->UpdateCollisions(true);
                else if (staticBody2) staticBody2->UpdateCollisions(true);

            } else {
                if (dynamicBody1) dynamicBody1->UpdateCollisions(false);
                else if (staticBody1) staticBody1->UpdateCollisions(false);

                if (dynamicBody2) dynamicBody2->UpdateCollisions(false);
                else if (staticBody2) staticBody2->UpdateCollisions(false);
            }
        }
      }


      for(auto& e : entities) {
        e->Update(1.0f / 60.f);
        //e->PhysicsUpdate(deltaTime);
        e->LateUpdate();
      }

      glfwPollEvents();
      glfwSwapBuffers(m_Window->GetGlfwWindow());
    }
  }
};

int main(int argc, char** argv) {
  auto ink = new Ink();

  ink->Run();
  glfwTerminate();
  return 0;
}