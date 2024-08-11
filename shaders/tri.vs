#version 330 core

layout (location = 0) in vec3 in_pos;

//uniform mat4 MVP;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main() {
    gl_Position = u_viewProjection * u_transform * vec4(in_pos, 1.0);
}
