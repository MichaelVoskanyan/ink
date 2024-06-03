cmake_minimum_required(VERSION 3.27)
project(Ink)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    "vendor/glad/include"
    "vendor/glfw/include"
    "vendor/glm_master"
    "ink/include"
)

add_subdirectory(vendor/glfw)

link_directories("vendor/glfw/src/Debug")

link_libraries(glfw)

set (GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set (GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set (GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentations")
set (GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

set(SOURCE_RENDERER
    "ink/src/renderer/buffers.cpp"
    "ink/src/renderer/vertexArray.cpp"
    "ink/src/renderer/renderObject.cpp"
    # "ink/src/renderer/renderer.cpp"
)

set(SOURCE_PHYSICS
    "ink/src/physics/physicsBase.cpp"
    "ink/src/physics/physicsEngine.cpp"
)

set(SOURCE_ECS
    "ink/src/ecs/entity.cpp"
    "ink/include/ecs/component.h"
    "ink/src/ecs/c_RenderObject.cpp"
)

set(SOURCE
    "vendor/glad/src/glad.c"
    "ink/src/core/window.cpp"
    "ink/src/core/shader.cpp"
    "ink/src/core/camera.cpp"
    "ink/src/core/main.cpp"
)

add_executable(Ink 
    ${SOURCE_RENDERER}
    ${SOURCE_ECS}
    ${SOURCE_PHYSICS}
    ${SOURCE}
)