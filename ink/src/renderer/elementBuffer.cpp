#include <renderer/elementBuffer.h>

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

ElementBuffer *ElementBuffer::Create(std::vector<uint32_t> elements) {
    auto eb = new ElementBuffer();
    eb->count = elements.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb->h_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eb->count * sizeof(uint32_t), &elements[0], GL_STATIC_DRAW);
    return eb;
}
