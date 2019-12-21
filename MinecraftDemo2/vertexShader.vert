#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec2 inTexIndex;

out vec2 texCoord;
out vec2 texIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	gl_Position =  projection * view * vec4(inPos,1.0f);
	texCoord = inTexCoord;
	texIndex = inTexIndex;
}