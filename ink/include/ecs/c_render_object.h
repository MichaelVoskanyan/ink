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

class CRenderObject : public Component {
public:
  CRenderObject(Entity* owner) : Component(owner) {
    shader = nullptr;
  }

  void Init();
  void Start();
  void Update(float deltaTime);
  void PhysicsUpdate(float fixedDeltaTime);
  void LateUpdate(float deltaTime);

  std::vector<float> vertices;
  std::vector<uint32_t> indices;

  void SetShader(std::shared_ptr<Shader> shader);

private:
  std::shared_ptr<RenderObject> renderObject;
  std::shared_ptr<Shader> shader;

  void UpdateTransformMatrix();
};
