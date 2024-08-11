#ifndef INK_WINDOW_H
#define INK_WINDOW_H

#include <typedefs.h>

struct GLFWwindow;

/**
 * Basic framebuffer size callback function. Effectively just used for function
 * pointer within glfwSetFramebufferSizeCallback(GLFWwindow *, function_name);
 */
void framebuffer_size_callback(GLFWwindow *wind, int width, int height);

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

struct WindowProps
{
    i32 width;
    i32 height;
    const char *title;

    WindowProps(i32 width = 800, i32 height = 600, const char *title = "Window")
        : width(width), height(height), title(title)
    {}
};

class Window
{
public:
    Window(const WindowProps &props = WindowProps());
    ~Window() {}

    void update();

    void set_vsync(bool enabled);
    bool is_vsync() const;

    GLFWwindow *get_glfw_window();

	static WindowProps s_windowProps;

	static i32 get_window_width();
	static i32 get_window_height();

	static void set_window_dimensions(i32 width, i32 height);

private:
    GLFWwindow *m_window;
};

#endif