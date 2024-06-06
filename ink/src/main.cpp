#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/render_object.h>
#include <renderer/vertex_array.h>

#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/c_render_object.h>
#include <ecs/c_character_controller.h>

#include <core/camera.h>
#include <core/shader.h>
#include <core/window.h>

#include <physics/physics_base.h>
#include <physics/physics_engine.h>

#include <core/application.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <memory>

uint16_t WIDTH = 800, HEIGHT = 600;
char* TITLE = "Ink";

class Ink : public Application {
public:
  Ink() {
    m_Window = std::unique_ptr<Window>(Window::Create());

    Start();
  }

  void Start() {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("/shaders/tri.vs", "/shaders/tri.fs");
    shader->use();

    // h_Rend->setActiveShaderHandle(shader);

    auto camera = Camera::GetInstance();

    std::vector<float> verts1 = {-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

    std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};

    std::shared_ptr<Entity> player = std::make_shared<Entity>();
    std::shared_ptr<CRenderObject> ro = player->AddComponent<CRenderObject>();
    std::shared_ptr<CCharacterController> cc = player->AddComponent<CCharacterController>();
    ro->vertices = verts1;
    ro->indices = physicsinds;
    ro->SetShader(shader);

    player->position = glm::vec3(0.f, 0.f, 0.f);
    player->rotation = glm::vec3(0.f);
    player->scale = glm::vec3(1.f);

    entities.push_back(player);

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

      for(auto& e : entities) {
        e->Update(deltaTime);
      }

      for(auto& e : entities) {
        e->PhysicsUpdate(deltaTime);
      }

      for(auto& e : entities) {
        e->LateUpdate(deltaTime);
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