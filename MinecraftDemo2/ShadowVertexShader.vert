#version 330 core

layout (location = 0) in vec3 inPos;

uniform mat4 lightSpaceMatrix;

void main(){
	gl_Position = lightSpaceMatrix * vec4(inPos, 1.0);
}