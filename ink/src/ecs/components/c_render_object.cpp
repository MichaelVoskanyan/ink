#include "c_render_object.h"
#include "ecs/entity.h"

#include <utility>

C_RenderObject::~C_RenderObject()
{
	m_renderObject.reset();
}

void C_RenderObject::init_render_object(Ref<RenderObject> renderObj)
{
	m_renderObject = std::move(renderObj);
	Renderer::get_instance()->queue_render_object(m_renderObject);
}

void C_RenderObject::init_render_object(Ref<VertexArray> vertexArray, Ref<Shader> shader)
{
	m_renderObject = std::make_shared<RenderObject>(vertexArray, shader, glm::mat4(1.f));
	Renderer::get_instance()->queue_render_object(m_renderObject);
}

void C_RenderObject::clear_render_object()
{
	auto renderInstance = Renderer::get_instance();
	renderInstance->remove_from_queue(m_renderObject);
	m_renderObject.reset();
}

void C_RenderObject::update_transform_matrix()
{
	auto transform = glm::mat4(1.f);
	transform = glm::translate(transform, m_owner->m_position);
	transform = transform * glm::mat4_cast(m_owner->m_rotation);
	transform = glm::scale(transform, m_owner->m_scale);

	m_renderObject->transform = transform;
}
void C_RenderObject::init()
{

}
void C_RenderObject::start()
{

}
void C_RenderObject::update(float deltaTime)
{
	update_transform_matrix();
}
void C_RenderObject::late_update()
{

}

