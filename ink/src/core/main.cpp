#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/renderer.h>
#include <renderer/vertexArray.h>
#include <renderer/renderObject.h>

#include <core/shader.h>
#include <core/camera.h>
#include <core/window.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

typedef uint32_t uint;

uint16_t WIDTH = 800, HEIGHT = 600;
char* TITLE = "Ink";

int main(int argc, char **argv) {

    auto wnd = new Window();
    wnd->i_windowHeight = HEIGHT;
    wnd->i_windowWidth = WIDTH;
    wnd->s_windowTitle = TITLE;

    wnd->InitWindow();
    
    Renderer *h_rend = Renderer::getInstance();

    std::vector<float> verts = {
        -0.5f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f
    };

    std::vector<uint> inds = { 0, 1, 2 };

    auto ro = RenderObject::Create(verts, inds);

    std::vector<float> nVerts = {
        -0.5f,  0.0f, 0.0f,
         0.5f,  0.0f, 0.0f,
         0.0f, -1.0f, 0.0f
    };

    std::vector<uint32_t> nInds = {1, 0, 2};

    auto ro2 = RenderObject::Create(nVerts, nInds);

    auto shader = new Shader("/shaders/tri.vs", "/shaders/tri.fs");

    shader->use();

    Camera *cam = new Camera();

    h_rend->setActiveShaderHandle(shader);

    h_rend->pushBackRenderQueue(ro);
    h_rend->pushBackRenderQueue(ro2);
    
    // -------------
    // MAIN LOOP
    // -------------
    while (!glfwWindowShouldClose(wnd->h_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // rendering bullshittery
        glm::mat4 view = cam->getView();
        glm::mat4 proj = cam->getProjection(WIDTH, HEIGHT);
        h_rend->drawQueue(view, proj);


        glfwPollEvents();
        glfwSwapBuffers(wnd->h_window);
    }

    return 0;
}
