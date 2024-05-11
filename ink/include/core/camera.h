//
// Created by micha on 1/28/2024.
//

#ifndef CESIUM_CAMERA_H
#define CESIUM_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
  float _fov = 55.0f, _nearClipPlane = 0.1f, _farClipPlane = 100.0f;
  glm::mat4 _view, _projection;

public:
  glm::vec3 _position, _front, _up;
  float _yaw = -90.0f, _pitch = 0, _roll = 0;

  Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

  ~Camera();

  void setPos(glm::vec3 pos);

  glm::mat4 getProjection(int width, int height);

  glm::mat4 getView();
};

#endif // CESIUM_CAMERA_H
