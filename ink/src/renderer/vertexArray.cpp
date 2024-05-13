#include <renderer/vertexArray.h>

#include <renderer/elementBuffer.h>
#include <renderer/vertexBuffer.h>

#include <glad/glad.h>

VertexArray::VertexArray() {
    glGenVertexArrays(1, &h_rendererID);
}

VertexArray::~VertexArray() {
    delete h_vertexBuffer;
    delete h_elementBuffer;
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

VertexArray *VertexArray::Create(std::vector<float> verts, std::vector<uint32_t> elements) {
    auto va = new VertexArray();
    glBindVertexArray(va->h_rendererID);
    va->h_vertexBuffer = VertexBuffer::Create(verts);
    va->h_elementBuffer = ElementBuffer::Create(elements);
    return va;
}
