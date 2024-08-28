#ifndef INK_RENDERER_H
#define INK_RENDERER_H

#include <typedefs.h>

#include "buffers.h"
#include "shader.h"

#include <glm/glm.hpp>

struct renderObject_t
{
    Ref<vertexArray_t> vertexArray;
    Ref<shader_t> shader;
    glm::mat4 transform;

    renderObject_t(Ref<vertexArray_t> vertexArray, Ref<shader_t> shader, glm::mat4 transform);
};

namespace ogl
{

void SetClearColor(const glm::vec4 &color);
void SetClearColor(f32 r, f32 g, f32 b, f32 a);
void Clear();
void SwapBuffers();
void Draw(shader_t &shader, vertexArray_t &vertexArray, const glm::mat4 &transform);
void Draw(renderObject_t &renderObject);

} // namespace ogl

class renderer_t
{
private:
    renderer_t();

public:
    renderer_t(const renderer_t &r) = delete;
    renderer_t &operator=(const renderer_t &r) = delete;

private:
    static renderer_t *s_instance;

    Vec<Ref<renderObject_t>> renderQueue_;

public:
    static glm::mat4 s_viewProjectionMatrix;

    static renderer_t *GetInstance();
    void QueueRenderObject(const Ref<renderObject_t> &renderObject);
    void RemoveFromQueue(const Ref<renderObject_t> &renderObject);
    void ClearRenderQueue();

    void DrawQueue() const;
};

#endif
