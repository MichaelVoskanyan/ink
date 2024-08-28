#ifndef INK_WINDOW_H
#define INK_WINDOW_H

#include <typedefs.h>

struct GLFWwindow;

/**
 * Basic framebuffer size callback function. Effectively just used for function
 * pointer within glfwSetFramebufferSizeCallback(GLFWwindow *, function_name);
 */
void FramebufferSizeCallback(GLFWwindow *wind, int width, int height);

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

struct windowProps_t
{
    i32 width;
    i32 height;
    const char *title;

    windowProps_t(i32 width = 800, i32 height = 600, const char *title = "Window")
        : width(width), height(height), title(title)
    {}
};

class window_t
{
public:
    window_t(const windowProps_t &props = windowProps_t());
    ~window_t() {}

    void Update();

    void SetVSync(bool enabled);
    bool IsVSync() const;

    GLFWwindow *GetGlfwWindow();


	static i32 GetWindowWidth();
	static i32 GetWindowHeight();

	static void SetWindowDimensions(i32 width, i32 height);

public:
	static windowProps_t s_windowProps;

private:
    GLFWwindow *window_;
};

#endif
