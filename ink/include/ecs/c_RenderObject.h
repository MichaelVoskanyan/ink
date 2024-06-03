#pragma once

#include "component.h"
#include <glm/glm.hpp>

#include <memory>
#include <cstdint>
#include <vector>

/* -- Forward Declarations -- */
class RenderObject;
class Shader;
class Camera;

class C_RenderObject : public Component {
public:
  C_RenderObject(Entity* owner) : Component(owner) {}

  void init();
  void start();
  void update(float deltaTime);
  void physicsUpdate(float fixedDeltaTime);
  void lateUpdate(float deltaTime);

  std::vector<float> vertices;
  std::vector<uint32_t> indices;

  void setShader(Shader* shader);

private:
  std::shared_ptr<RenderObject> renderObject;
  Shader* shader;

  void updateTransformMatrix();
};
