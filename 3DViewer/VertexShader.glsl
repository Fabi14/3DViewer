#version 330 core
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec4 _col;
layout (location = 2) in vec3 _nor;

out vec4 vertexColor;

uniform mat4 modelTransform;

void main()
{
    gl_Position = modelTransform * vec4(_pos, 1.0);
    vertexColor = _col;
}