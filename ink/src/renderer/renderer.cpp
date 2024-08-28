#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

renderObject_t::renderObject_t(Ref<vertexArray_t> vertexArray, Ref<shader_t> shader, glm::mat4 transform)
		:vertexArray(vertexArray), shader(shader), transform(transform)
{ }

namespace ogl
{

void SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void SetClearColor(f32 r, f32 g, f32 b, f32 a)
{
	glClearColor(r, g, b, a);
}

void Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SwapBuffers()
{
	glfwSwapBuffers(glfwGetCurrentContext());
}

void Draw(shader_t& shader, vertexArray_t& vertexArray, const glm::mat4& transform)
{
	shader.Bind();
	vertexArray.Bind();

	shader.SetMat4("u_viewProjection", renderer_t::s_viewProjectionMatrix);
	shader.SetMat4("u_transform", transform);

	glDrawElements(GL_TRIANGLES, vertexArray.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
}

}	// namespace ogl

glm::mat4 renderer_t::s_viewProjectionMatrix = glm::mat4(1.f);
renderer_t* renderer_t::s_instance = nullptr;

renderer_t::renderer_t()
{
	renderQueue_ = Vec<Ref<renderObject_t>>();
}

renderer_t *renderer_t::GetInstance()
{
	if (nullptr == s_instance)
	{
		s_instance = new renderer_t();
	}
	return s_instance;
}

void renderer_t::QueueRenderObject(const Ref<renderObject_t>& renderObject)
{
	renderQueue_.push_back(renderObject);
}

void renderer_t::RemoveFromQueue(const Ref<renderObject_t> &renderObject)
{
	auto obj = std::find(renderQueue_.begin(), renderQueue_.end(), renderObject);
	renderQueue_.erase(obj);
}

void renderer_t::ClearRenderQueue()
{
	renderQueue_.clear();
}

void renderer_t::DrawQueue() const
{
	ogl::Clear();

	for (auto& o : renderQueue_)
	{
		o->shader->Bind();
		o->vertexArray->Bind();

//		RenderAPI::draw(*o);
		o->shader->SetMat4("u_viewProjection", renderer_t::s_viewProjectionMatrix);
		o->shader->SetMat4("u_transform", o->transform);

		glDrawElements(GL_TRIANGLES, o->vertexArray->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

	ogl::SwapBuffers();
}
