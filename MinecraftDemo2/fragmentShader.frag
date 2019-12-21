#version 330 core

uniform sampler2DArray ourTexture;

in vec2 texCoord;
in vec2 texIndex;

out vec4 FragColor;

void main(){
	FragColor = texture(ourTexture,vec3(texCoord,texIndex.x));
}