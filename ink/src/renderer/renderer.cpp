#include <renderer/renderer.h>
#include <renderer/renderObject.h>
#include <core/shader.h>

Renderer* Renderer::h_instance = nullptr;

Renderer::Renderer() {
    queue = std::vector<RenderObject*>();
    h_shader = NULL;
}

void Renderer::setGlfwWindowInst(GLFWwindow *win) {
    this->h_window = win;
}

void Renderer::setActiveShaderHandle(Shader *shader) {
    this->h_shader = shader;
}

Renderer *Renderer::getInstance() {
    if (h_instance == NULL) {
        h_instance = new Renderer();

        return h_instance;
    } else {
        return h_instance;
    }
}

void Renderer::pushBackRenderQueue(RenderObject* rendObj) {
    this->queue.push_back(rendObj);
}

void Renderer::clearRenderQueue() {
    this->queue.clear();
}

void Renderer::drawQueue(glm::mat4 view, glm::mat4 proj) {
    if (h_shader == NULL) 
        return;
    if (h_instance == NULL)
        return;

    h_shader->use();

    glm::mat4 mvp = glm::mat4(1.f);
    mvp *= proj;
    mvp *= view;

    for (auto a : queue) {
        a->drawRenderObject(h_shader, mvp);
    }
}
