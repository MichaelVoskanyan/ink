#ifndef INK_VERTEXBUFFER_H
#define INK_VERTEXBUFFER_H

#include <vector>
#include <iostream>

typedef uint32_t uint;

class VertexBuffer {
private:
    uint h_rendererID;
    uint size;

public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    static VertexBuffer *Create(std::vector<float> vertices);
};

#endif