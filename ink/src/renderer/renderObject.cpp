#include <renderer/renderObject.h>
#include <renderer/vertexArray.h>
#include <core/shader.h>

RenderObject::RenderObject() {
    _position = glm::vec3(0.f);
    _rotation = glm::vec3(0.f);
    _scale = glm::vec3(1.f);
}

RenderObject* RenderObject::Create(std::vector<float> verts, std::vector<uint32_t> inds) {
    auto ro = new RenderObject();
    auto va = VertexArray::Create(verts, inds);
    ro->vao = va;

    return ro;
}

glm::mat4 RenderObject::getModelMat() {
    glm::mat4 model = glm::mat4(1.f);
    model = glm::translate(model, _position);
    model = glm::scale(model, _scale);

    return model;
}

void RenderObject::position(glm::vec3 position) { _position = position; }
void RenderObject::rotation(glm::vec3 rotation) { _rotation = rotation; }
void RenderObject::scale(glm::vec3 scale) { _scale = scale; }

glm::vec3 RenderObject::position() { return _position; }
glm::vec3 RenderObject::rotation() { return _rotation; }
glm::vec3 RenderObject::scale() { return _scale; }

void RenderObject::drawRenderObject(Shader *shader, glm::mat4 vp) {
    vao->Bind();
    shader->setMat4("MVP", vp * getModelMat());
    glDrawElements(GL_TRIANGLES, vao->GetCount(), GL_UNSIGNED_INT, nullptr);
}
