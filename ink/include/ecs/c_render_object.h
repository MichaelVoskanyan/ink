#pragma once

#include "component.h"
#include <glm/glm.hpp>
#include <memory>
#include <cstdint>
#include <vector>
#include <cmath>
#include <stdexcept>

/* -- Forward Declarations -- */
class RenderObject;
class Shader;
class Camera;

enum class ShapeType { Triangle, Square, Circle };

class CRenderObject : public Component {
public:
  CRenderObject(Entity* owner) : Component(owner) {
    shader = nullptr;
  }

  void Init();
  void Start();
  void Update(float deltaTime);
  void PhysicsUpdate(float fixedDeltaTime);
  void LateUpdate();

  void SetShape(ShapeType shapeType, float size);
  void SetShader(std::shared_ptr<Shader> shader);

  std::vector<float> vertices;
  std::vector<uint32_t> indices;

private:
  std::shared_ptr<RenderObject> renderObject;
  std::shared_ptr<Shader> shader;

  void UpdateTransformMatrix();
};
