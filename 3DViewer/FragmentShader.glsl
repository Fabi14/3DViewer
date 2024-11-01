#version 330 core

in vec4 vertexColor;
in vec3 vertexPos;
in vec3 vertexNorm;
in vec2 vertexUVs;

out vec4 fragColor;

uniform vec4 lightColor = {1.,1.,1.,1.};
uniform vec3 lightPos = {100.,100.,0.};

uniform vec3 viewPos;
uniform sampler2D baseColorTexture;

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



//    if(gl_FragCoord.x < 320)
    {
        fragColor = (ambient + diffuse + specular)* texture(baseColorTexture,vertexUVs);
    }
//    else
//    {
//        fragColor = (ambient + diffuse + specular)* vertexColor;
//    }
//
}