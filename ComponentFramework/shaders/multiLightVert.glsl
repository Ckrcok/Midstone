#version 450
#extension GL_ARB_separate_shader_objects : enable

// Attributes 
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPos[4];
uniform vec4 diffuse[4];
uniform vec4 specular[4];

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 eyeDir;
layout(location = 2) out vec2 texCoord;
layout(location = 3) out vec3 lightDir[4];
layout(location = 13) out vec4 diffuseFrag[4];
layout(location = 23) out vec4 specularFrag[4];

void main() {
    
    for (int x = 0; x < diffuse.length; x++)
    {
        diffuseFrag[x] = diffuse[x];
        specularFrag[x] = specular[x];
    }
   

    texCoord = uvCoord;
    texCoord.y *= -1.0;
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    vertNormal = normalize(normalMatrix * vNormal); /// Rotate the normal to the correct orientation

    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;

    for (int li = 0; li < lightDir.length; li++)
    {
        lightDir[li] = normalize(lightPos[li] - vertPos); 
    }

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
}