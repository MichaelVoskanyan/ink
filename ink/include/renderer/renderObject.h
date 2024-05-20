#ifndef INK_RENDEROBJECT_H
#define INK_RENDEROBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class VertexArray;
class Shader;

class RenderObject {
private:
    VertexArray* vao;

    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

public:

    RenderObject();
    glm::mat4 getModelMat();

    void position(glm::vec3);
    void rotation(glm::vec3);
    void scale(glm::vec3);

    glm::vec3 position();
    glm::vec3 rotation();
    glm::vec3 scale();

    static RenderObject* Create(std::vector<float> verts, std::vector<uint32_t> inds);

    void drawRenderObject(Shader* shader, glm::mat4 mvp);
    
};


#endif