#ifndef INK_ELEMENTBUFFER_H
#define INK_ELEMENTBUFFER_H

#include <vector>
#include <stdint.h>
#include <iostream>

class ElementBuffer {
private:
    uint32_t h_rendererID;
    uint32_t count;

public:
    ElementBuffer();
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;

    uint32_t GetCount() const;

    static ElementBuffer *Create(std::vector<uint32_t> elements);
};

#endif
