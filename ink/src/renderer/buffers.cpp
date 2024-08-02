#include "buffers.h"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(const Vec<u32> &indices) :m_rendererID(0), m_count(indices.size())
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(u32), &indices[0], GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

u32 IndexBuffer::get_count() const
{
    return m_count;
}

VertexBuffer::VertexBuffer(const Vec<f32> &vertices) :m_rendererID(0), m_size(vertices.size() * sizeof(f32))
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, m_size, &vertices[0], GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray(const Vec<f32> &vertices, const Vec<u32> &indices)
    :m_rendererID(0), m_vertexBuffer(nullptr), m_indexBuffer(nullptr)
{
    glGenVertexArrays(1, &m_rendererID);
    glBindVertexArray(m_rendererID);

	m_vertexBuffer = std::make_unique<VertexBuffer>(vertices);
	m_indexBuffer = std::make_unique<IndexBuffer>(indices);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(6 * sizeof(f32)));
}

VertexArray::VertexArray(Scope<VertexBuffer> vertexBuffer, Scope<IndexBuffer> indexBuffer)
	: m_rendererID(0), m_vertexBuffer(std::move(vertexBuffer)), m_indexBuffer(std::move(indexBuffer))
{
	glGenVertexArrays(1, &m_rendererID);
	glBindVertexArray(m_rendererID);

	m_vertexBuffer->bind();
	m_indexBuffer->bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(3 * sizeof(f32)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(6 * sizeof(f32)));
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_rendererID);
	m_vertexBuffer->bind();
	m_indexBuffer->bind();
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

u32 VertexArray::get_index_count() const
{
	return m_indexBuffer->get_count();
}
