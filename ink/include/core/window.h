#ifndef INK_WINDOW_H
#define INK_WINDOW_H

#include <stdint.h>

struct GLFWwindow;

/**
 * Basic framebuffer size callback function. Effectively just used for function
 * pointer within glfwSetFramebufferSizeCallback(GLFWwindow *, function_name);
 */
void framebuffer_size_callback(GLFWwindow* wind, int width, int height);

// struct Window {
//   // Data for window creation
//   uint32_t i_windowWidth; // window initial width
//   uint32_t i_windowHeight; // window initial height
//   char* s_windowTitle; // C string for window title (top bar)

//   GLFWwindow* h_window; // Handle to GLFWwindow

//   /**
//    * Handles window initialization and creation. Initializes GLFW,
//    * GLAD, creates window, sets current context, and sets h_window to
//    * the newly created GLFWwindow.
//    */
//   void InitWindow();
// };

struct WindowProps {
  uint32_t width;
  uint32_t height;
  const char* title;

  WindowProps(uint32_t width = 800, uint32_t height = 600, const char* title = "Window")
      : width(width), height(height), title(title) {}
};

class Window {
public:
  Window(const WindowProps& props = WindowProps());
  ~Window() {}

  void Update();

  void SetVSync(bool enabled);
  bool IsVSync() const;

  GLFWwindow* GetGlfwWindow();

  static Window* Create(const WindowProps& props = WindowProps());

private:
  GLFWwindow* m_Window;
};

#endif