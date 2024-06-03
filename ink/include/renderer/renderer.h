#ifndef INK_RENDERER_H
#define INK_RENDERER_H

#include <vector>

#include <glm/glm.hpp>

//--------------------------
// FORWARD DECLARATIONS
//--------------------------

struct GLFWwindow;
class RenderObject;
class Shader;

class Renderer {
private:
  GLFWwindow *h_window;
  Shader *h_shader;
  std::vector<RenderObject *> queue;

  Renderer();

public:
  static Renderer *h_instance;
  Renderer(const Renderer &rend) = delete;

  static Renderer *getInstance();
  void setGlfwWindowInst(GLFWwindow *win);
  void setActiveShaderHandle(Shader *shader);

  void pushBackRenderQueue(RenderObject *rendObj);
  void clearRenderQueue();

  void drawQueue(glm::mat4 view, glm::mat4 proj);
};

#endif