#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/render_object.h>
#include <renderer/vertex_array.h>

#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/c_render_object.h>
#include <ecs/c_character_controller.h>
#include <ecs/c_physics_body.h>

#include <core/camera.h>
#include <core/shader.h>
#include <core/window.h>

#include <physics/physics_base.h>
#include <physics/physics_engine.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <memory>

uint16_t WIDTH = 800, HEIGHT = 600;
char* TITLE = "Ink";

int main(int argc, char** argv) {
  float lastFrame = 0.f;
  float deltaTime;

  // auto h_Rend = Renderer::getInstance();
  std::unique_ptr<Window> h_Window = std::unique_ptr<Window>(Window::Create());

  auto shader = std::make_shared<Shader>("/shaders/tri.vs", "/shaders/tri.fs");
  shader->use();

  // h_Rend->setActiveShaderHandle(shader);

  auto camera = Camera::GetInstance();

  std::vector<float> verts1 = {-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

  std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};

  auto player = std::make_shared<Entity>();
  auto ro = player->AddComponent<CRenderObject>();
  auto cc = player->AddComponent<CCharacterController>();
  auto pb = player->AddComponent<CPhysicsBody>();
  ro->SetShape(ShapeType::Circle, 0.5f);
  ro->SetShader(shader.get());

  player->position = glm::vec3(0.f, 0.f, 0.f);
  player->rotation = glm::vec3(0.f);
  player->scale = glm::vec3(1.f);

  player->Init();
  player->Start();

  /* -- MAIN LOOP -- */

  while(!glfwWindowShouldClose(glfwGetCurrentContext())) {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    player->Update(deltaTime);
    player->PhysicsUpdate(deltaTime);
    player->LateUpdate(deltaTime);

    // h_Rend->drawQueue(camera->getView(), camera->getProjection(WIDTH, HEIGHT));

    // Poll events and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(glfwGetCurrentContext());
  }

  h_Window.reset();
  glfwTerminate();
  return 0;
}