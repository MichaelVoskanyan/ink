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
class camera_t
{
private:
    float fov_ = 55.0f, nearClipPlane_ = 0.1f, farClipPlane_ = 100.0f;
    glm::mat4 view_, projection_;

    camera_t() {}
    static camera_t *s_instance;

public:
    glm::vec3 position_ = glm::vec3(0.f, 0.f, 3.f);
    glm::vec3 front_ = glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 up_ = glm::vec3(0.f, 1.f, 0.f);
    float yaw_ = -90.0f, pitch_ = 0, roll_ = 0;

    static camera_t *GetInstance();

    camera_t(const camera_t &obj) = delete;

    // Pretty self explanitory
    void SetPosition(glm::vec3 pos);

    /**
     * Returns matrix 4x4 of the projection. Takes in
     * int width = width of glViewport (draw space)
     * int height = height of glViewport ^
     */
    glm::mat4 GetProjection(int width, int height);

    /**
     * Returns matrix 4x4 of the camera view. This function
     * relies on member variables fov, near and far clip planes,
     * and the directions front and up.
     */
    glm::mat4 GetView();
};

#endif // CESIUM_CAMERA_H
