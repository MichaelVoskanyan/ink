#ifndef INK_VERTEXARRAY_H
#define INK_VERTEXARRAY_H

#include <iostream>
#include <vector>

class VertexBuffer;
class ElementBuffer;

typedef uint32_t uint;

class VertexArray {
private:
    uint h_rendererID;
    VertexBuffer* h_vertexBuffer;
    ElementBuffer* h_elementBuffer;

public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    uint32_t GetCount() const;

    static VertexArray *Create(std::vector<float> verts, std::vector<uint> elements);
};

#endif