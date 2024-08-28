#include <renderer/camera.h>

camera_t *camera_t::s_instance = nullptr;

camera_t *camera_t::GetInstance()
{
    if(s_instance == nullptr)
    {
        s_instance = new camera_t();
    }
    return s_instance;
}

void camera_t::SetPosition(glm::vec3 pos)
{
	position_ = pos;
}

glm::mat4 camera_t::GetProjection(int width, int height)
{
	projection_ = glm::perspective(glm::radians(fov_), (float)width / (float)height, nearClipPlane_, farClipPlane_);
    return projection_;
}

glm::mat4 camera_t::GetView()
{
	view_ = glm::lookAt(position_, position_ + front_, up_);
    return view_;
}
