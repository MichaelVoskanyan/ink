#ifndef INK_RENDERER_H
#define INK_RENDERER_H

#include <typedefs.h>

#include "buffers.h"
#include "shader.h"

#include <glm/glm.hpp>

struct RenderObject
{
    Ref<VertexArray> vertexArray;
    Ref<Shader> shader;
    glm::mat4 transform;

    RenderObject(Ref<VertexArray> vertexArray, Ref<Shader> shader, glm::mat4 transform);
};

namespace RenderAPI
{

void set_clear_color(const glm::vec4 &color);
void set_clear_color(f32 r, f32 g, f32 b, f32 a);
void clear();
void swap_buffers();
void draw(Shader &shader, VertexArray &vertexArray, const glm::mat4 &transform);
void draw(RenderObject &renderObject);

} // namespace RenderAPI

class Renderer
{
private:
    Renderer();

public:
    Renderer(const Renderer &r) = delete;
    Renderer &operator=(const Renderer &r) = delete;

private:
    static Renderer *s_instance;

    Vec<Ref<RenderObject>> m_renderQueue;

public:
    static glm::mat4 s_viewProjectionMatrix;

    static Renderer *get_instance();
    void queue_render_object(const Ref<RenderObject> &renderObject);
    void remove_from_queue(const Ref<RenderObject> &renderObject);
    void clear_render_queue();

    void draw_queue() const;
};

#endif