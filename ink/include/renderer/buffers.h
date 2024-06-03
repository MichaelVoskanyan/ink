#ifndef INK_BUFFERS_H
#define INK_BUFFERS_H

#include <vector>
#include <cstdint>
#include <iostream>

/**
 * ElementBuffer class definition contains reference to the element buffer
 * handle h_rendererID as well as uint32_t count (element count).
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

  static std::shared_ptr<ElementBuffer> Create(std::vector<uint32_t> elements);
};

/**
 * VertexBuffer class definition contains reference to the vertex buffer
 * handle h_rendererID as well as uint32_t size in bytes (sizeof(float) *
 * std::vector.size()).
 */

class VertexBuffer {
private:
  uint32_t h_rendererID;
  uint32_t size;

public:
  VertexBuffer();
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;

  static std::shared_ptr<VertexBuffer> Create(std::vector<float> vertices);
};

#endif