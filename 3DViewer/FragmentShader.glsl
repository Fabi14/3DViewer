#version 330 core

in vec4 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform vec3 lightDir;

uniform vec4 lightColor ={1.,1.,1.,1.};

void main()
{
    float diff = max(dot(vertexNormal, lightDir),0.);
    vec4 diffuse = diff * lightColor;
    fragColor = vertexColor * diffuse;
}