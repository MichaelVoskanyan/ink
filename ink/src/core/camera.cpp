#include <core/camera.h>

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) {
  _position = pos;
  _front = front;
  _up = up;
  _projection = glm::mat4(1.0f);
}

Camera::~Camera() {}

void Camera::setPos(glm::vec3 pos) { _position = pos; }

glm::mat4 Camera::getProjection(int width, int height) {
  _projection =
      glm::perspective(glm::radians(_fov), (float)width / (float)height,
                       _nearClipPlane, _farClipPlane);
  return _projection;
}

glm::mat4 Camera::getView() {
  _view = glm::lookAt(_position, _position + _front, _up);
  return _view;
}
