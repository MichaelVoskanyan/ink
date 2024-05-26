#ifndef INK_ELEMENTBUFFER_H
#define INK_ELEMENTBUFFER_H

#include <vector>
#include <stdint.h>
#include <iostream>

/**
 * ElementBuffer class definition contains reference to the element buffer handle h_rendererID
 * as well as uint32_t count (element count).
*/

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
