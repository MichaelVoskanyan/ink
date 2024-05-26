//
// Created by micha on 1/28/2024.
//

#ifndef CESIUM_CAMERA_H
#define CESIUM_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/** 
 * Base declaration of Camera class
 * contains constructor and member functions for handling changes in position,
 * calculating view matrix, and calculating projection matrix.
 * 
 * Member variables include the field of view, near and far clipping planes of 
 * view frustum, as well as camera yaw, pitch, roll, position, & front + up vectors.
 * Front is dead simple in 2d, but will require constant changes based on the yaw, pitch
 * and roll of camera in 3d environment.
*/
class Camera {
private:
  float _fov = 55.0f, _nearClipPlane = 0.1f, _farClipPlane = 100.0f;
  glm::mat4 _view, _projection;

public:
  glm::vec3 _position, _front, _up;
  float _yaw = -90.0f, _pitch = 0, _roll = 0;

  /** 
   * Camera base constructor with default values
   * position by default is 0, 0, 3
   * front is always z = -1.0f
   * up is always y = 1.0f
   * 
   * Defaults for front and up are unchanged in 2D environment. Dynamic in 3d
  */
  Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

  ~Camera();

  // Pretty self explanitory
  void setPos(glm::vec3 pos);

  /**
   * Returns matrix 4x4 of the projection. Takes in 
   * int width = width of glViewport (draw space)
   * int height = height of glViewport ^
  */
  glm::mat4 getProjection(int width, int height);

  /**
   * Returns matrix 4x4 of the camera view. This function
   * relies on member variables fov, near and far clip planes,
   * and the directions front and up.
  */
  glm::mat4 getView();
};

#endif // CESIUM_CAMERA_H
