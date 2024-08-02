#ifndef INK_BUFFERS_H
#define INK_BUFFERS_H

#include <typedefs.h>

class IndexBuffer
{
private:
    u32 m_rendererID;
    u32 m_count;

public:
    IndexBuffer(const Vec<u32> &indices);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    u32 get_count() const;
};

class VertexBuffer
{
private:
    u32 m_rendererID;
    u32 m_size;

public:
    VertexBuffer(const Vec<f32> &vertices);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

class VertexArray
{
private:
    u32 m_rendererID;
    Scope<VertexBuffer> m_vertexBuffer;
    Scope<IndexBuffer> m_indexBuffer;

public:
    VertexArray(const Vec<f32> &vertices, const Vec<u32> &indices);
    VertexArray(Scope<VertexBuffer> vertBuf, Scope<IndexBuffer> indexBuf);

    ~VertexArray();

    void bind() const;
    void unbind() const;

    u32 get_index_count() const;
};

#endif