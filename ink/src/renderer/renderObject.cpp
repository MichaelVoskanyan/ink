#include <renderer/renderObject.h>
#include <renderer/vertexArray.h>
#include <core/shader.h>
#include <memory>

RenderObject::RenderObject() {
  _model = glm::mat4(1.f);
}

// RenderObject* RenderObject::Create(std::vector<float> verts, std::vector<uint32_t> inds) {
//   auto ro = new RenderObject();
//   auto va = VertexArray::Create(verts, inds);
//   ro->_vao = va;

//   return ro;
// }

std::shared_ptr<RenderObject> RenderObject::Create(std::vector<float> verts, std::vector<uint32_t> inds) {
  auto ro = std::make_shared<RenderObject>();
  ro->_vao = VertexArray::Create(verts, inds);

  return ro;
}

void RenderObject::setModelMat(glm::mat4 mat) {
  this->_model = mat;
}

void RenderObject::drawRenderObject(Shader* shader, glm::mat4 vp) {
  _vao->Bind();
  shader->setMat4("MVP", vp * _model);
  glDrawElements(GL_TRIANGLES, _vao->GetCount(), GL_UNSIGNED_INT, nullptr);
}
