#version 330 core
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec4 _col;
layout (location = 2) in vec3 _nor;

out vec4 vertexColor;
out vec3 vertexPos;
out vec3 vertexNorm;

uniform mat4 modelTransform;
uniform mat3 modelTransformNormal;

uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(_pos, 1.0);
    vertexColor = _col;
    vertexPos = (modelTransform * vec4(_pos, 1.0)).xyz;
    vertexNorm = normalize(modelTransformNormal * _nor);
}