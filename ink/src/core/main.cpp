#include <renderer/vertexArray.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    

    std::vector<float> verts = {
        -0.5f, -0.5f, 0.f, 
         0.5f, -0.5f, 0.f,
         0.0f,  0.5f, 0.f
    };

    std::vector<uint> inds = { 0, 1, 2 };

    auto va = VertexArray::Create(verts, inds);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


    auto shader = new Shader("/shaders/tri.vs", "/shaders/tri.fs");

    shader->use();

    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(0.f));
    model = glm::scale(model, glm::vec3(1.f));

    Camera *cam = new Camera();
    

    // ---------
    // MAIN LOOP
    // ---------
    while (!glfwWindowShouldClose(wnd->h_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // rendering bullshittery
        glm::mat4 mvp = glm::mat4(1.f);
        mvp *= cam->getProjection(WIDTH, HEIGHT);
        mvp *= cam->getView();
        mvp *= model;

        shader->setMat4("MVP", mvp);
        va->Bind();
        glDrawElements(GL_TRIANGLES, va->GetCount(), GL_UNSIGNED_INT, (void*)NULL);


        glfwPollEvents();
        glfwSwapBuffers(wnd->h_window);
    }

    return 0;
}
