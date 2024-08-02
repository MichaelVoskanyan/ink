#include <core/window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *wind, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(const WindowProps &props)
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title, nullptr, nullptr);

    if(!m_window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        exit(1);
    }

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    glClearColor(0.2f, 0.2f, 0.3f, 1.f);
}

GLFWwindow *Window::get_glfw_window()
{
    if(!m_window)
    {
        return nullptr;
    }
    return m_window;
}

Window *Window::create(const WindowProps &props)
{
    Window *win = new Window(props);
    return win;
}
