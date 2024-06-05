#ifndef INK_VERTEXARRAY_H
#define INK_VERTEXARRAY_H

#include <iostream>
#include <vector>
#include <memory>
#include <stdint.h>

class VertexBuffer;
class ElementBuffer;

typedef uint32_t uint;

class VertexArray {
private:
  uint h_rendererID;
  std::shared_ptr<VertexBuffer> h_vertexBuffer;
  std::shared_ptr<ElementBuffer> h_elementBuffer;

public:
  VertexArray();
  ~VertexArray();

  void Bind() const;
  void Unbind() const;

  uint32_t GetCount() const;

  static std::shared_ptr<VertexArray> Create(std::vector<float> verts, std::vector<uint> elements);
};

#endif