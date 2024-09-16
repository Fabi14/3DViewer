#version 330 core
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec4 _col;
layout (location = 2) in vec3 _nor;

out vec4 vertexColor;
out vec3 vertexNormal;
out vec3 vertexPos;

uniform mat4 modelTransform;
uniform mat3 modelNormalTransform;

void main()
{
    gl_Position = modelTransform * vec4(_pos, 1.0);
    vertexNormal = normalize(modelNormalTransform * _nor);
    vertexColor = _col;
    vertexPos= gl_Position.xyz;
}