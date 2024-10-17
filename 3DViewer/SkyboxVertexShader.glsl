#version 330 core

layout (location = 0) in vec3 _pos;

out vec3 texCoords;

uniform mat4 viewTransform;
uniform mat4 projectionTransform;

void main()
{
	texCoords = _pos;
	gl_Position = (projectionTransform * viewTransform * vec4(_pos,1.0)).xyww;
}
