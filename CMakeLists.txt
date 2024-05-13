cmake_minimum_required(VERSION 3.27)
project(Ink)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    "vendor/glad/include"
    "vendor/glfw/include"
    "vendor/glm_master"
    "ink/include"
)

link_directories(
    "vendor/glfw/lib-vc2022"
)

link_libraries(glfw3)

set(SOURCE_RENDERER
    "ink/src/renderer/vertexBuffer.cpp"
    "ink/src/renderer/elementBuffer.cpp"
    "ink/src/renderer/vertexArray.cpp"
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
    ${SOURCE}
)