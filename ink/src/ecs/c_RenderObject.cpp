#include <ecs/c_RenderObject.h>
#include <ecs/entity.h>

#include <renderer/renderObject.h>
#include <renderer/renderer.h>
#include <core/camera.h>
#include <core/shader.h>

#include <glm/gtc/matrix_transform.hpp>

void C_RenderObject::init() {
  renderObject = RenderObject::Create(vertices, indices);
  // auto h_Renderer = Renderer::getInstance();
  // h_Renderer->pushBackRenderQueue(renderObject);
}

void C_RenderObject::start() {}

void C_RenderObject::update(float deltaTime) {
  updateTransformMatrix();
}

void C_RenderObject::physicsUpdate(float fixedDeltaTime) {}

void C_RenderObject::lateUpdate(float deltaTime) {
  glm::mat4 vp = glm::mat4(1.f);
  auto h_cam = Camera::getInstance();
  vp *= h_cam->getProjection(800, 600);
  vp *= h_cam->getView();
  renderObject->drawRenderObject(shader, vp);
}

void C_RenderObject::updateTransformMatrix() {
  glm::mat4 transform = glm::mat4(1.f);
  transform = glm::translate(transform, owner->position);

  transform = glm::rotate(transform, glm::radians(owner->rotation.x), glm::vec3(1.f, 0.f, 0.f));
  transform = glm::rotate(transform, glm::radians(owner->rotation.y), glm::vec3(0.f, 1.f, 0.f));
  transform = glm::rotate(transform, glm::radians(owner->rotation.z), glm::vec3(0.f, 0.f, 1.f));

  transform = glm::scale(transform, owner->scale);
  renderObject->setModelMat(transform);
}

void C_RenderObject::setShader(Shader* shader) {
  this->shader = shader;
}
