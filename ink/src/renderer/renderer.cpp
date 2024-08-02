#include "renderer.h"

#include <GLFW/glfw3.h>

RenderObject::RenderObject(Ref<VertexArray> vertexArray, Ref<Shader> shader, glm::mat4 transform)
		:vertexArray(vertexArray), shader(shader), transform(transform)
{ }

namespace RenderAPI
{

void set_clear_color(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void set_clear_color(f32 r, f32 g, f32 b, f32 a)
{
	glClearColor(r, g, b, a);
}

void clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void swap_buffers()
{
	glfwSwapBuffers(glfwGetCurrentContext());
}

void draw(Shader& shader, VertexArray& vertexArray, const glm::mat4& transform)
{
	shader.bind();
	vertexArray.bind();

	shader.set_mat4("u_viewProjection", Renderer::s_viewProjectionMatrix);
	shader.set_mat4("u_transform", transform);

	glDrawElements(GL_TRIANGLES, vertexArray.get_index_count(), GL_UNSIGNED_INT, nullptr);
}

void draw(Scope<RenderObject> renderObject)
{
	renderObject->shader->bind();
	renderObject->vertexArray->bind();

	renderObject->shader->set_mat4("u_viewProjection", Renderer::s_viewProjectionMatrix);
	renderObject->shader->set_mat4("u_transform", renderObject->transform);

	glDrawElements(GL_TRIANGLES, renderObject->vertexArray->get_index_count(), GL_UNSIGNED_INT, nullptr);
}


}	// namespace RenderAPI

glm::mat4 Renderer::s_viewProjectionMatrix = glm::mat4(1.f);
Renderer* Renderer::s_instance = nullptr;

Renderer::Renderer()
{
	m_renderQueue = Vec<Ref<RenderObject>>();
}

Renderer *Renderer::get_instance()
{
	if (nullptr == s_instance)
	{
		s_instance = new Renderer();
	}
	return s_instance;
}

void Renderer::queue_render_object(const Ref<RenderObject>& renderObject)
{
	m_renderQueue.push_back(renderObject);
}

void Renderer::remove_from_queue(const Ref<RenderObject> &renderObject)
{
	auto obj = std::find(m_renderQueue.begin(), m_renderQueue.end(), renderObject);
	m_renderQueue.erase(obj);
}

void Renderer::clear_render_queue()
{
	m_renderQueue.clear();
}

void Renderer::draw_queue() const
{
	for (auto& o : m_renderQueue)
	{
		o->shader->bind();
		o->vertexArray->bind();

//		o->shader->set_mat4("u_viewProjection", s_viewProjectionMatrix);
//		o->shader->set_mat4("u_transform", o->transform);

//		o->shader->set_mat4("MVP", s_viewProjectionMatrix * o->transform);

		o->shader->set_mat4("MVP", o->transform);
		glDrawElements(GL_TRIANGLES, o->vertexArray->get_index_count(), GL_UNSIGNED_INT, nullptr);

	}
}