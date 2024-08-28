#include "buffers.h"

#include <glad/glad.h>

indexBuffer_t::indexBuffer_t(const Vec<u32> &indices) :rendererID_(0), count_(indices.size())
{
    glGenBuffers(1, &rendererID_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_ * sizeof(u32), &indices[0], GL_STATIC_DRAW);
}

indexBuffer_t::~indexBuffer_t()
{
    glDeleteBuffers(1, &rendererID_);
}

void indexBuffer_t::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
}

void indexBuffer_t::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

u32 indexBuffer_t::GetCount() const
{
    return count_;
}

vertexBuffer_t::vertexBuffer_t(const Vec<f32> &vertices) :rendererID(0), size_(vertices.size() * sizeof(f32))
{
    glGenBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, size_, &vertices[0], GL_STATIC_DRAW);
}

vertexBuffer_t::~vertexBuffer_t()
{
    glDeleteBuffers(1, &rendererID);
}

void vertexBuffer_t::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void vertexBuffer_t::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

vertexArray_t::vertexArray_t(const Vec<f32> &vertices, const Vec<u32> &indices)
    :rendererID_(0), vertexBuffer_(nullptr), indexBuffer_(nullptr)
{
    glGenVertexArrays(1, &rendererID_);
    glBindVertexArray(rendererID_);

	vertexBuffer_ = std::make_unique<vertexBuffer_t>(vertices);
	indexBuffer_ = std::make_unique<indexBuffer_t>(indices);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(6 * sizeof(f32)));
}

vertexArray_t::vertexArray_t(Scope<vertexBuffer_t> vertexBuffer, Scope<indexBuffer_t> indexBuffer)
	: rendererID_(0), vertexBuffer_(std::move(vertexBuffer)), indexBuffer_(std::move(indexBuffer))
{
	glGenVertexArrays(1, &rendererID_);
	glBindVertexArray(rendererID_);

	vertexBuffer_->Bind();
	indexBuffer_->Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(3 * sizeof(f32)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), (void *)(6 * sizeof(f32)));
}

vertexArray_t::~vertexArray_t()
{
    glDeleteVertexArrays(1, &rendererID_);
}

void vertexArray_t::Bind() const
{
    glBindVertexArray(rendererID_);
	vertexBuffer_->Bind();
	indexBuffer_->Bind();
}

void vertexArray_t::Unbind() const
{
	glBindVertexArray(0);
}

u32 vertexArray_t::GetIndexCount() const
{
	return indexBuffer_->GetCount();
}
