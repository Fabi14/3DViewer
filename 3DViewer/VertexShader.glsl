#version 330 core
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec4 _col;

out vec4 vecCol;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(_pos, 1.0);
    vecCol = _col;
}