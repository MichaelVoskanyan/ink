#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/shader.h>
#include <core/camera.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

typedef uint32_t uint;

uint16_t WIDTH = 800, HEIGHT = 600;
char* TITLE = "Ink";

int main(int argc, char **argv) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(.5f, .25f, 0.f, 1.f);

    std::vector<float> verts = {
        -0.5f, -0.5f, 0.f, 
         0.5f, -0.5f, 0.f,
         0.0f,  0.5f, 0.f
    };

    std::vector<uint> inds = { 0, 1, 2 };

    uint VAO, VBO, IBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(uint), &inds[0], GL_STATIC_DRAW);

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
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // rendering bullshittery
        glm::mat4 mvp = glm::mat4(1.f);
        mvp *= cam->getProjection(WIDTH, HEIGHT);
        mvp *= cam->getView();
        mvp *= model;

        shader->setMat4("MVP", mvp);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, inds.size(), GL_UNSIGNED_INT, (void*)NULL);


        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    return 0;
}
