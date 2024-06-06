#include <ecs/c_render_object.h>
#include <ecs/entity.h>

#include <renderer/render_object.h>
#include <renderer/renderer.h>
#include <core/camera.h>
#include <core/shader.h>

#include <glm/gtc/matrix_transform.hpp>

void CRenderObject::Init() {
  renderObject = RenderObject::Create(vertices, indices);
}

void CRenderObject::Start() {}

void CRenderObject::Update(float deltaTime) {
  UpdateTransformMatrix();
}

void CRenderObject::PhysicsUpdate(float fixedDeltaTime) {}

void CRenderObject::LateUpdate(float deltaTime) {
  glm::mat4 vp = glm::mat4(1.f);
  auto h_cam = Camera::GetInstance();
  vp *= h_cam->GetProjection(800, 600);
  vp *= h_cam->GetView();
  renderObject->DrawRenderObject(shader, vp);
}


void CRenderObject::UpdateTransformMatrix() {
  glm::mat4 transform = glm::mat4(1.f);

  transform = glm::translate(transform, owner->position);

  transform = glm::rotate(transform, glm::radians(owner->rotation.x), glm::vec3(1.f, 0.f, 0.f));
  transform = glm::rotate(transform, glm::radians(owner->rotation.y), glm::vec3(0.f, 1.f, 0.f));
  transform = glm::rotate(transform, glm::radians(owner->rotation.z), glm::vec3(0.f, 0.f, 1.f));

  transform = glm::scale(transform, owner->scale);
  renderObject->SetModelMat(transform);
}

void CRenderObject::SetShape(ShapeType shapeType, float size) {
    vertices.clear();
    indices.clear();

    switch (shapeType) {
        case ShapeType::Triangle: {
            float halfSize = size / 2.0f;
            float height = std::sqrt(size * size - halfSize * halfSize);

            vertices = {
                0.0f, height, 0.0f,
                -halfSize, 0.0f, 0.0f,
                halfSize, 0.0f, 0.0f
            };

            indices = { 0, 1, 2 };

            break;
        }
        case ShapeType::Square: {
            float halfSize = size / 2.0f;

            vertices = {
                -halfSize, halfSize, 0.0f,
                -halfSize, -halfSize, 0.0f,
                halfSize, -halfSize, 0.0f,
                halfSize, halfSize, 0.0f
            };

            indices = {
                0, 1, 2,
                2, 3, 0
            };

            break;
        }
        case ShapeType::Circle: {
            const int segments = 36;
            float angleIncrement = 2.0f * 3.14159265358979323846f / segments;

            vertices.push_back(0.0f); // Center vertex
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);

            for (int i = 0; i <= segments; ++i) {
                float angle = i * angleIncrement;
                float x = size * std::cos(angle);
                float y = size * std::sin(angle);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(0.0f);

                if (i > 0) {
                    indices.push_back(0);
                    indices.push_back(i);
                    indices.push_back(i + 1);
                }
            }

            indices.back() = 1; // Connect the last triangle to the first

            break;
        }
        default:
            throw std::invalid_argument("Unsupported shape type");
    }
}

void CRenderObject::SetShader(Shader* shader) {
  this->shader = shader;
}
