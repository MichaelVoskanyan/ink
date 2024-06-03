#include <renderer/vertexArray.h>

#include <renderer/buffers.h>

#include <glad/glad.h>

VertexArray::VertexArray() {
  glGenVertexArrays(1, &h_rendererID);
}

VertexArray::~VertexArray() {
  h_elementBuffer.reset();
  h_vertexBuffer.reset();
  glDeleteVertexArrays(1, &h_rendererID);
}

void VertexArray::Bind() const {
  glBindVertexArray(h_rendererID);
}

void VertexArray::Unbind() const {
  glBindVertexArray(0);
}

uint32_t VertexArray::GetCount() const {
  return this->h_elementBuffer->GetCount();
}

std::shared_ptr<VertexArray> VertexArray::Create(std::vector<float> verts, std::vector<uint32_t> elements) {
  auto va = std::make_shared<VertexArray>();
  glBindVertexArray(va->h_rendererID);
  va->h_vertexBuffer = VertexBuffer::Create(verts);
  va->h_elementBuffer = ElementBuffer::Create(elements);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  return va;
}
