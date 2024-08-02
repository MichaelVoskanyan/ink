#include <renderer/camera.h>

Camera *Camera::s_instance = nullptr;

Camera *Camera::get_instance()
{
    if(s_instance == nullptr)
    {
        s_instance = new Camera();
    }
    return s_instance;
}

void Camera::set_pos(glm::vec3 pos)
{
	m_position = pos;
}

glm::mat4 Camera::get_projection(int width, int height)
{
	m_projection = glm::perspective(glm::radians(m_fov), (float)width / (float)height, m_nearClipPlane, m_farClipPlane);
    return m_projection;
}

glm::mat4 Camera::get_view()
{
	m_view = glm::lookAt(m_position, m_position + m_front, m_up);
    return m_view;
}
