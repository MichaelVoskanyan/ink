#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/renderObject.h>
#include <renderer/renderer.h>
#include <renderer/vertexArray.h>

#include <core/camera.h>
#include <core/shader.h>
#include <core/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

typedef uint32_t uint;

uint16_t WIDTH = 800, HEIGHT = 600;
char *TITLE = "Ink";

// void keyCallback(GLFWwindow* window, int key, int scancode, int action, int
// mods) {
//     if (action == GLFW_PRESS) {
//         if (key == GLFW_KEY_W) {
//             std::cout << "W key pressed" << std::endl;
//         }
//         // ... (rest of your key checks)
//     }
// }

int main(int argc, char **argv) {

  auto wnd = new Window();
  wnd->i_windowHeight = HEIGHT;
  wnd->i_windowWidth = WIDTH;
  wnd->s_windowTitle = TITLE;

  wnd->InitWindow();

  Renderer *h_rend = Renderer::getInstance();

  std::vector<float> verts = {-0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
                              0.0f,  0.0f, 1.0f, 0.0f};

  std::vector<uint> inds = {0, 1, 2};

  auto ro = RenderObject::Create(verts, inds);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  // glfwSetKeyCallback(wnd->h_window, keyCallback);

  auto shader = new Shader("/shaders/tri.vs", "/shaders/tri.fs");

  shader->use();

  glm::mat4 model = glm::mat4(1.f); // Initialize model matrix outside the loop
  Camera *cam = new Camera();

  h_rend->setActiveShaderHandle(shader);

  h_rend->pushBackRenderQueue(ro);
  // h_rend->pushBackRenderQueue(ro2);

  // -------------
  // MAIN LOOP
  // -------------
  while (!glfwWindowShouldClose(wnd->h_window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::vec3 translationVector(0.0f, 0.0f, 0.0f); // Initial translation vector
    const float translationSpeed = 0.01f;          // Speed of translation
    if (glfwGetKey(wnd->h_window, GLFW_KEY_W) == GLFW_PRESS)
      translationVector.y += translationSpeed;
    if (glfwGetKey(wnd->h_window, GLFW_KEY_S) == GLFW_PRESS)
      translationVector.y -= translationSpeed;
    if (glfwGetKey(wnd->h_window, GLFW_KEY_A) == GLFW_PRESS)
      translationVector.x -= translationSpeed;
    if (glfwGetKey(wnd->h_window, GLFW_KEY_D) == GLFW_PRESS)
      translationVector.x += translationSpeed;

    // Apply translation to the model matrix
    model = glm::translate(model, translationVector);

    glm::mat4 view = cam->getView();
    glm::mat4 proj = cam->getProjection(800, 600);

    // Create the MVP matrix
    // glm::mat4 mvp = glm::mat4(1.f);
    // mvp *= cam->getProjection(WIDTH, HEIGHT);
    // mvp *= cam->getView();
    // mvp *= model;

    // Set the MVP matrix in the shader
    // shader->setMat4("MVP", mvp);

    // Bind vertex array and draw
    // va->Bind();
    // glDrawElements(GL_TRIANGLES, va->GetCount(), GL_UNSIGNED_INT,
    // (void*)NULL);
    h_rend->drawQueue(view, proj);

    // Poll events and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(wnd->h_window);
  }

  return 0;
}