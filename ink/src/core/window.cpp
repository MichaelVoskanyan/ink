#include <core/window.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void Window::InitWindow() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    h_window = glfwCreateWindow(i_windowWidth, i_windowHeight, s_windowTitle, NULL, NULL);

    if (!h_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(h_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, i_windowWidth, i_windowHeight);
    glClearColor(.5f, .25f, 0.f, 1.f);
}
