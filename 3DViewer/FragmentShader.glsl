#version 330 core

in vec4 vertexColor;
in vec3 vertexNormal;
in vec3 vertexPos;

out vec4 fragColor;

uniform vec3 lightPos= {10.,10.,0.};

uniform vec4 lightColor ={1.,1.,1.,1.};

uniform vec3 viewPos = {0.,0.,-1.};


void main()
{
    float amientStrenght = 0.1;
    vec4 ambient = amientStrenght * lightColor;
    
    float diffuseStrength = 0.8;
    vec3 lightDir =  normalize(vertexPos - lightPos);
    float diff = max(dot(vertexNormal, lightDir),0.);
    vec4 diffuse = diffuseStrength * diff * lightColor;

    float specularStrenght = 0.8;

    vec3 reflectDir = normalize(reflect(-lightDir, vertexNormal));

    vec3 viewDir = normalize(viewPos-vertexPos); 
    float spec = pow(max(dot(viewDir, reflectDir),0.),64);
    vec4 specular = specularStrenght * spec * lightColor;
     

    fragColor = vec4((vertexColor * (ambient + diffuse + specular)).xyz, 1.0);
}