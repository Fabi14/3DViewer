#version 330 core

in vec4 vecCol;

out vec4 fragColor;

uniform mat4 model;

void main()
{
    fragColor = vecCol;
}