#ifndef INK_RENDEROBJECT_H
#define INK_RENDEROBJECT_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class VertexArray;
class Shader;

class RenderObject {
private:
  std::shared_ptr<VertexArray> _vao;
  glm::mat4 _model;

public:
  RenderObject();
  void setModelMat(glm::mat4 mat);

  // static RenderObject* Create(std::vector<float> verts, std::vector<uint32_t> inds);
  static std::shared_ptr<RenderObject> Create(std::vector<float> verts, std::vector<uint32_t> inds);

  void drawRenderObject(Shader* shader, glm::mat4 mvp);
};

#endif