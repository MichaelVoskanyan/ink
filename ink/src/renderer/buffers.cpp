#include <renderer/buffers.h>

#include <glad/glad.h>

ElementBuffer::ElementBuffer() {
  glGenBuffers(1, &h_rendererID);
}

ElementBuffer::~ElementBuffer() {
  glDeleteBuffers(1, &h_rendererID);
}

void ElementBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, h_rendererID);
}

void ElementBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t ElementBuffer::GetCount() const {
  return count;
}

std::shared_ptr<ElementBuffer> ElementBuffer::Create(std::vector<uint32_t> elements) {
  auto eb = std::make_shared<ElementBuffer>();
  eb->count = elements.size();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb->h_rendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, eb->count * sizeof(uint32_t), &elements[0], GL_STATIC_DRAW);
  return eb;
}

VertexBuffer::VertexBuffer() {
  glGenBuffers(1, &h_rendererID);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &h_rendererID);
}

void VertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, h_rendererID);
}

void VertexBuffer::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(std::vector<float> vertices) {
  auto vb = std::make_shared<VertexBuffer>();
  vb->size = vertices.size() * sizeof(float);
  glBindBuffer(GL_ARRAY_BUFFER, vb->h_rendererID);
  glBufferData(GL_ARRAY_BUFFER, vb->size, &vertices[0], GL_STATIC_DRAW);
  return vb;
}
