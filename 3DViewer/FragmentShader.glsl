#version 330 core

in vec4 vertexColor;
in vec3 vertexNormal;

out vec4 fragColor;

uniform vec3 lightDir;

uniform vec4 lightColor ={1.,1.,1.,1.};

uniform vec3 viewPos = {0.,0.,-1.};

in vec3 vertexPos;

void main()
{
    float amientStrenght = 0.1;
    vec4 ambient = amientStrenght * lightColor;
    
    float diffuseStrength = 1.0;
    float diff = max(dot(vertexNormal, lightDir),0.);
    vec4 diffuse = diffuseStrength * diff * lightColor;

    float specularStrenght = 0.5;
    vec3 reflectDir = reflect(-lightDir, vertexNormal);

    vec3 viewDir = normalize(viewPos-vertexPos); 
    float spec = pow(max(dot(viewDir, reflectDir),0.),32);
    vec4 specular = specularStrenght * spec * lightColor;
     

    fragColor = vec4((vertexColor * (ambient + diffuse + specular)).xyz, 1.0);
}