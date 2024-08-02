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
class Camera
{
private:
    float m_fov = 55.0f, m_nearClipPlane = 0.1f, m_farClipPlane = 100.0f;
    glm::mat4 m_view, m_projection;

    Camera() {}
    static Camera *s_instance;

public:
    glm::vec3 m_position = glm::vec3(0.f, 0.f, 3.f);
    glm::vec3 m_front = glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 m_up = glm::vec3(0.f, 1.f, 0.f);
    float m_yaw = -90.0f, m_pitch = 0, m_roll = 0;

    static Camera *get_instance();

    Camera(const Camera &obj) = delete;

    // Pretty self explanitory
    void set_pos(glm::vec3 pos);

    /**
     * Returns matrix 4x4 of the projection. Takes in
     * int width = width of glViewport (draw space)
     * int height = height of glViewport ^
     */
    glm::mat4 get_projection(int width, int height);

    /**
     * Returns matrix 4x4 of the camera view. This function
     * relies on member variables fov, near and far clip planes,
     * and the directions front and up.
     */
    glm::mat4 get_view();
};

#endif // CESIUM_CAMERA_H
