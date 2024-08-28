#include "c_render_object.h"
#include "ecs/entity.h"

#include <utility>

cRenderObject_t::~cRenderObject_t()
{
	renderObject_.reset();
}

void cRenderObject_t::InitRenderObject(Ref<renderObject_t> renderObj)
{
	renderObject_ = std::move(renderObj);
	renderer_t::GetInstance()->QueueRenderObject(renderObject_);
}

void cRenderObject_t::InitRenderObject(Ref<vertexArray_t> vertexArray, Ref<shader_t> shader)
{
	renderObject_ = std::make_shared<renderObject_t>(vertexArray, shader, glm::mat4(1.f));
	renderer_t::GetInstance()->QueueRenderObject(renderObject_);
}

void cRenderObject_t::ClearRenderObject()
{
	auto renderInstance = renderer_t::GetInstance();
	renderInstance->RemoveFromQueue(renderObject_);
	renderObject_.reset();
}

void cRenderObject_t::UpdateTransformMatrix()
{
	auto transform = glm::mat4(1.f);
	transform = glm::translate(transform, owner_->position_);
	transform = transform * glm::mat4_cast(owner_->rotation_);
	transform = glm::scale(transform, owner_->scale_);

	renderObject_->transform = transform;
}
void cRenderObject_t::Init()
{

}
void cRenderObject_t::Start()
{

}
void cRenderObject_t::Update(float deltaTime)
{
	UpdateTransformMatrix();
}
void cRenderObject_t::LateUpdate()
{

}
