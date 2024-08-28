#include <core/window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

windowProps_t window_t::s_windowProps = NULL;

void FramebufferSizeCallback(GLFWwindow *wind, int width, int height)
{
    glViewport(0, 0, width, height);
	std::cout << "Window resized\n";
	window_t::SetWindowDimensions(width, height);
}

window_t::window_t(const windowProps_t &props)
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(1);
    }

	s_windowProps = props;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow((int)props.width, (int)props.height, props.title, nullptr, nullptr);

    if(!window_)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window_);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        exit(1);
    }

    glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);

    glClearColor(0.2f, 0.2f, 0.3f, 1.f);
}

GLFWwindow *window_t::GetGlfwWindow()
{
    if(!window_)
    {
        return nullptr;
    }
    return window_;
}

i32 window_t::GetWindowWidth()
{
	return s_windowProps.width;
}

i32 window_t::GetWindowHeight()
{
	return s_windowProps.height;
}

void window_t::SetWindowDimensions(i32 width, i32 height)
{
	s_windowProps.width = width;
	s_windowProps.height = height;
}
