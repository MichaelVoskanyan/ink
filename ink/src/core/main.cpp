#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/renderObject.h>
// #include <renderer/renderer.h>
#include <renderer/vertexArray.h>

#include <ecs/entity.h>
#include <ecs/component.h>
#include <ecs/c_RenderObject.h>

#include <core/camera.h>
#include <core/shader.h>
#include <core/window.h>

#include <physics/physicsBase.h>
#include <physics/physicsEngine.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <memory> // <------ THIS FUCKING BULLSHIT

typedef uint32_t uint;

uint16_t WIDTH = 800, HEIGHT = 600;
char* TITLE = "Ink";

int main(int argc, char** argv) {
  float lastFrame = 0.f;
  float deltaTime;

  // auto h_Rend = Renderer::getInstance();

  auto wnd = new Window();
  wnd->i_windowHeight = HEIGHT;
  wnd->i_windowWidth = WIDTH;
  wnd->s_windowTitle = TITLE;

  wnd->InitWindow();

  auto shader = new Shader("/shaders/tri.vs", "/shaders/tri.fs");
  shader->use();

  // h_Rend->setActiveShaderHandle(shader);

  auto camera = Camera::getInstance();

  std::vector<float> verts1 = {-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f};

  std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};

  auto player = std::make_shared<Entity>();
  auto ro = player->AddComponent<C_RenderObject>();
  ro->vertices = verts1;
  ro->indices = physicsinds;
  ro->setShader(shader);

  player->position = glm::vec3(0.f, 0.f, 0.f);
  player->rotation = glm::vec3(0.f);
  player->scale = glm::vec3(1.f);

  player->init();
  player->start();

  /* -- MAIN LOOP -- */

  while(!glfwWindowShouldClose(wnd->h_window)) {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    player->update(deltaTime);
    player->physicsUpdate(deltaTime);
    player->lateUpdate(deltaTime);

    // h_Rend->drawQueue(camera->getView(), camera->getProjection(WIDTH, HEIGHT));

    // Poll events and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(wnd->h_window);
  }

  return 0;
}