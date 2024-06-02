#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/renderer.h>
#include <renderer/vertexArray.h>
#include <renderer/renderObject.h>

#include <core/shader.h>
#include <core/camera.h>
#include <core/window.h>

#include <physics/physicsBase.h>
#include <physics/physicsEngine.h>

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

    // std::vector<float> verts = {
    //     -0.5f, 0.0f, 0.0f,
    //      0.5f, 0.0f, 0.0f,
    //      0.0f, 1.0f, 0.0f
    // };

    // std::vector<uint> inds = { 0, 1, 2 };

    // auto ro = RenderObject::Create(verts, inds);

    // std::vector<float> nVerts = {
    //     -0.5f,  0.0f, 0.0f,
    //      0.5f,  0.0f, 0.0f,
    //      0.0f, -1.0f, 0.0f
    // };

    //   std::vector<uint32_t> nInds = {1, 0, 2};

    // auto ro2 = RenderObject::Create(nVerts, nInds);

    auto shader = new Shader("/shaders/tri.vs", "/shaders/tri.fs");

    shader->use();

    Camera *cam = new Camera();

    h_rend->setActiveShaderHandle(shader);


    PhysicsEngine* physics = new PhysicsEngine();

    std::vector<float> verts1 = {
        -0.5f,  -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};
    
    auto physicsobject1 = RenderObject::Create(verts1, physicsinds);

    // std::vector<float> verts2 = {
    //     2.0f,  2.0f, 0.0f,
    //     2.0f,  3.0f, 0.0f,
    //     3.0f, 3.0f, 0.0f,
    //     3.0f, 2.0f, 0.0f
    // };


    PhysicsBody* body1 = new PhysicsBody(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.5f));
    // PhysicsBody* body2 = new PhysicsBody(glm::vec3(3.0f), glm::vec3(1.0f));
    h_rend->pushBackRenderQueue(physicsobject1);
    
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
