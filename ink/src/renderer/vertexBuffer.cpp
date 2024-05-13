#include <renderer/vertexBuffer.h>

#include <glad/glad.h>

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

VertexBuffer *VertexBuffer::Create(std::vector<float> vertices) {
    auto vb = new VertexBuffer();
    vb->size = vertices.size() * sizeof(float);
    glBindBuffer(GL_ARRAY_BUFFER, vb->h_rendererID);
    glBufferData(GL_ARRAY_BUFFER, vb->size, &vertices[0], GL_STATIC_DRAW);
    return vb;
}
