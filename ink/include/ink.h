#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/render_object.h"
#include "renderer/vertex_array.h"

#include "ecs/entity.h"
#include "ecs/component.h"
#include "ecs/components/c_render_object.h"
#include "ecs/components/c_character_controller.h"
#include "ecs/components/c_physics_body.h"
#include "ecs/components/c_box_collider.h"

#include "core/camera.h"
#include "core/shader.h"
#include "core/window.h"
#include "core/application.h"

#include "physics/physics_base.h"
#include "physics/physics_engine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>