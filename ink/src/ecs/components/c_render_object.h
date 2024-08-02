#ifndef INK_C_RENDER_OBJECT_H
#define INK_C_RENDER_OBJECT_H

#include <typedefs.h>
#include <ecs/component.h>
#include "renderer/renderer.h"

class C_RenderObject : public Component
{
public:
	explicit C_RenderObject(Entity* owner) : Component(owner) {}
	~C_RenderObject();

	void init_render_object(Ref<RenderObject> renderObj);
	void init_render_object(Ref<VertexArray> vertexArray, Ref<Shader> shader);
	void clear_render_object();

	void update_transform_matrix();

	void init() override;
	void start() override;
	void update(float deltaTime) override;
	void late_update() override;

private:
	Ref<RenderObject> m_renderObject;
};

#endif
