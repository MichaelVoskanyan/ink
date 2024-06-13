cmake_minimum_required(VERSION 3.21)
project(Ink)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    "vendor/glad/include"
    "vendor/glfw/include"
    "vendor/GLM"
    "ink/include"
)

add_subdirectory(vendor/glfw)

link_directories("vendor/glfw/src/Debug")

set(CMAKE_BUILD_TYPE Debug)

set (GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set (GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set (GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentations")
set (GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

set(SOURCE_RENDERER
    "ink/src/renderer/buffers.cpp"
    "ink/src/renderer/vertex_array.cpp"
    "ink/src/renderer/render_object.cpp"
    # "ink/src/renderer/renderer.cpp"
)

set(SOURCE_PHYSICS
    "ink/src/physics/physics_base.cpp"
    "ink/src/physics/physics_engine.cpp"
)

set(SOURCE_ECS
    "ink/src/ecs/entity.cpp"
    "ink/include/ecs/component.h"
    "ink/src/ecs/c_render_object.cpp"
    "ink/src/ecs/c_character_controller.cpp"
    "ink/src/ecs/c_physics_body.cpp"
    "ink/src/ecs/c_box_collider.cpp"
)

set(SOURCE
    "vendor/glad/src/glad.c"
    "ink/src/core/window.cpp"
    "ink/src/core/shader.cpp"
    "ink/src/core/camera.cpp"
    "ink/src/main.cpp"
)

add_executable(Ink 
    ${SOURCE_RENDERER}
    ${SOURCE_ECS}
    ${SOURCE_PHYSICS}
    ${SOURCE}
)

target_link_libraries(Ink glfw)