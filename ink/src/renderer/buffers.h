#ifndef INK_BUFFERS_H
#define INK_BUFFERS_H

#include <typedefs.h>

class indexBuffer_t
{
private:
    u32 rendererID_;
    u32 count_;

public:
    indexBuffer_t(const Vec<u32> &indices);
    ~indexBuffer_t();

    void Bind() const;
    void Unbind() const;

    u32 GetCount() const;
};

class vertexBuffer_t
{
private:
    u32 rendererID;
    u32 size_;

public:
    vertexBuffer_t(const Vec<f32> &vertices);
    ~vertexBuffer_t();

    void Bind() const;
    void Unbind() const;
};

class vertexArray_t
{
private:
    u32 rendererID_;
    Scope<vertexBuffer_t> vertexBuffer_;
    Scope<indexBuffer_t> indexBuffer_;

public:
    vertexArray_t(const Vec<f32> &vertices, const Vec<u32> &indices);
    vertexArray_t(Scope<vertexBuffer_t> vertBuf, Scope<indexBuffer_t> indexBuf);

    ~vertexArray_t();

    void Bind() const;
    void Unbind() const;

    u32 GetIndexCount() const;
};

#endif
