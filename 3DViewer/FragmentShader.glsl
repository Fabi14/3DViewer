#version 330 core

in vec4 vertexColor;
in vec3 vertexPos;
in vec3 vertexNorm;

out vec4 fragColor;

uniform vec4 lightColor = {1.,1.,1.,1.};
uniform vec3 lightPos = {10.,10.,0.};

uniform vec3 viewPos = {0.,0.,-1.};

void main()
{
    float ambientStrength = .3;
    vec4 ambient = ambientStrength * lightColor;
    
    float diffuseStrength = 1.;
    vec3 lightDir = normalize(vertexPos - lightPos);
    float diff = max(dot(vertexNorm,lightDir),0.);
    vec4 diffuse = diffuseStrength * diff * lightColor;


    float specularStrenght = 0.8;
    vec3 refDir = reflect(-lightDir, vertexNorm);
    vec3 viewDir = normalize(viewPos-vertexPos); 
    float spec = pow(max(dot(viewDir,refDir),0.),32);
    vec4 specular = specularStrenght* spec * lightColor;

    fragColor = (ambient + diffuse + specular)* vertexColor;
}