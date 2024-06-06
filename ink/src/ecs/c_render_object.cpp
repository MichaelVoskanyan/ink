#include <ecs/c_render_object.h>
#include <ecs/entity.h>

#include <renderer/render_object.h>
#include <renderer/renderer.h>
#include <core/camera.h>
#include <core/shader.h>

#include <glm/gtc/matrix_transform.hpp>

void CRenderObject::Init() {
  renderObject = RenderObject::Create(vertices, indices);
}

void CRenderObject::Start() {}

void CRenderObject::Update(float deltaTime) {
  UpdateTransformMatrix();
}

void CRenderObject::PhysicsUpdate(float fixedDeltaTime) {}

void CRenderObject::LateUpdate(float deltaTime) {
  glm::mat4 vp = glm::mat4(1.f);
  auto h_cam = Camera::GetInstance();
  vp *= h_cam->GetProjection(800, 600);
  vp *= h_cam->GetView();
  renderObject->DrawRenderObject(shader.get(), vp);
}

void CRenderObject::UpdateTransformMatrix() {
  glm::mat4 transform = glm::mat4(1.f);

  transform = glm::translate(transform, owner->position);

  transform = glm::rotate(transform, glm::radians(owner->rotation.x), glm::vec3(1.f, 0.f, 0.f));
  transform = glm::rotate(transform, glm::radians(owner->rotation.y), glm::vec3(0.f, 1.f, 0.f));
  transform = glm::rotate(transform, glm::radians(owner->rotation.z), glm::vec3(0.f, 0.f, 1.f));

  transform = glm::scale(transform, owner->scale);
  renderObject->SetModelMat(transform);
}

void CRenderObject::SetShader(std::shared_ptr<Shader> shader) {
  this->shader = shader;
}
