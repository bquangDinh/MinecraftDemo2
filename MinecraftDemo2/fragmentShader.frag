#version 330 core

uniform sampler2DArray ourTexture;
uniform sampler2D depthMap;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float ambientStregth;

in vec2 texCoord;
in vec2 texIndex;
in vec3 FragPos;
in vec4 FragPosLightSpace;
in vec3 Normal;

out vec4 FragColor;

float ShadowCalculation(vec4 FragPosLightSpace){
	vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	vec3 lightDir = normalize(-lightPos);
	float bias = max(0.05 * (1.0 - dot(Normal, lightDir)), 0.005);
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
	return shadow;
}

vec3 calculateLighting(){
	vec3 ambient = ambientStregth * lightColor;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-lightPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	float shadow = ShadowCalculation(FragPosLightSpace);
	vec3 result = (ambient + (1.0 - shadow) * diffuse);
	return result;
}

void main(){
	vec3 result = calculateLighting();
	FragColor = texture(ourTexture,vec3(texCoord,texIndex.x)) * vec4(result,1.0);
}