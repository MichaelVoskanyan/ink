#ifndef INK_C_RENDER_OBJECT_H
#define INK_C_RENDER_OBJECT_H

#include <typedefs.h>
#include <ecs/component.h>
#include "renderer/renderer.h"

class cRenderObject_t : public component_t
{
public:
	explicit cRenderObject_t(entity_t* owner) : component_t(owner) {}
	~cRenderObject_t();

	void InitRenderObject(Ref<renderObject_t> renderObj);
	void InitRenderObject(Ref<vertexArray_t> vertexArray, Ref<shader_t> shader);
	void ClearRenderObject();

	void UpdateTransformMatrix();

	void Init() override;
	void Start() override;
	void Update(float deltaTime) override;
	void LateUpdate() override;

private:
	Ref<renderObject_t> renderObject_;
};

#endif
