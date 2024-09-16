#version 330 core

in vec4 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform vec3 lightDir;

uniform vec4 lightColor ={1.,1.,1.,1.};

uniform vec3 viewDir = {0.,0.,-1.};

void main()
{
    float amientStrenght = 0.1;
    vec4 ambient = amientStrenght * lightColor;
    
    float diffuseStrength = 0.8;
    float diff = max(dot(vertexNormal, lightDir),0.);
    vec4 diffuse = diffuseStrength * diff * lightColor;

    float specularStrenght = 0.5;
    vec3 reflectDir = reflect(-lightDir, vertexNormal);

    float spec = pow(max(dot(viewDir, reflectDir),0.),16);
    vec4 specular = specularStrenght * spec * lightColor;


    fragColor = (ambient + diffuse + specular) * vertexColor;
}