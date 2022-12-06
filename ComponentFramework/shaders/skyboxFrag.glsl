#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = 0) in vec3 texCoord;

uniform samplerCube skyboxTexture;

layout(location = 0) out vec4 fragColor;

void main() 
{	
	vec3 texCoordXCorrection = vec3 (-texCoord.x, texCoord.y, texCoord.z);
	fragColor = texture(skyboxTexture, texCoordXCorrection);	
}